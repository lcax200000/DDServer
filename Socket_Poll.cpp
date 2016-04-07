#include "Socket_Poll.h"
 socket_server SOCKET_SERVER;
static void records(int per_recv, int max_recv)
{
	RecvNums = 0;
	char filename[128] = { 0, };
	char con[128] = { 0, };

	sprintf(con, "平均接收: %d  最大接收: %d\r\n", per_recv, max_recv);
	strcpy(filename, "records.txt");
	//FILE* fd = fopen(filename, "a");
	//int res = fwrite(con, strlen(con), 1, fd);
	//fclose(fd);

}



void sigroutine(int signo) 
{
	//printf("signo \r\n", signo);
	//long 	_re = RecvNums;
	switch (signo) 
    {
	case SIGALRM:
		++CurTimes;

		if (CurTimes == 60)
		{
			CurTimes = 0;
			int perr = AllRecv / 60;
			printf("perr %d MaxRecv %d  AllRecv %d \r\n", perr, MaxRecv, AllRecv);
			AllRecv = 0;
			
			records(perr, MaxRecv);
		}
		else
		{
			AllRecv += RecvNums;
			if (MaxRecv < RecvNums)
			{
				MaxRecv = RecvNums;
			}
			RecvNums = 0;
		}

		break;
	case SIGVTALRM:
		printf("RecvNums %d MaxRecv %d  AllRecv %d \r\n", RecvNums, MaxRecv, AllRecv);
		break;
	}
	return;
}


int do_listen(int handle, int port, int block)
{
	
	int lisSock = socket(AF_INET, SOCK_STREAM, 0);
	int reuse = 1;
	setsockopt(lisSock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

	int flag;
	flag = fcntl(lisSock, F_GETFL);
	fcntl(lisSock, F_SETFL, flag | O_NONBLOCK);

	struct sockaddr_in lisAddr;
	lisAddr.sin_family = AF_INET;
	lisAddr.sin_port = htons(port);
	lisAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(lisSock, (struct sockaddr *)&lisAddr, sizeof(lisAddr)) == -1)
	{
		perror("bind");
		return -1;
	}

	listen(lisSock, block);

	connection_st* ptc = (connection_st*)(Allocator_Manager::instance()->malloc(sizeof(connection_st)));
	ptc->sock = lisSock;
	ptc->type = T_ACCEPT;
	ptc->service_handle = handle;

	ptc->epfd = lisSock%EPOLL_NUM;


	struct epoll_event evReg;
	evReg.events = EPOLLIN;
	evReg.data.ptr = ptc;

	SOCKET_SERVER.slot[lisSock] = ptc;
	int res = epoll_ctl(SOCKET_SERVER.epfd[lisSock%EPOLL_NUM], EPOLL_CTL_ADD, lisSock, &evReg);
	if (res != 0)
	{
		perror("epoll_ctl");
	}


	return lisSock;
}

int do_accept(connection_st* conn)
{
	int sock = accept(conn->sock, NULL, NULL);
	int keepalive = 1;
	if (sock > 0)
	{
		int flag;
		flag = fcntl(sock, F_GETFL);
		fcntl(sock, F_SETFL, flag | O_NONBLOCK);


		setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepalive, sizeof(keepalive));
		connection_st* ptc = (connection_st*)(Allocator_Manager::instance()->malloc(sizeof(connection_st)));
		//connection_st* ptc = new connection_st;
		ptc->sock = sock;
		ptc->rbuf = new Stream_Base(10240);
		//ptc->wbuf = new Stream_Base();
		ptc->type = T_CONNECT;
		ptc->service_handle = conn->service_handle;
		struct epoll_event evReg;
		//evReg.events = EPOLLIN;
		//evReg.data.fd = sock;
		evReg.events = EPOLLIN | EPOLLONESHOT;

		evReg.data.ptr = ptc;
		ptc->epfd = sock%EPOLL_NUM;


		Message msg(sock, SOCKET_TYPE_CONNECT, NULL);
		ServiceMgr::instance()->GetService(conn->service_handle)->Push(msg);

		SOCKET_SERVER.slot[sock] = ptc;
		epoll_ctl(SOCKET_SERVER.epfd[sock%EPOLL_NUM], EPOLL_CTL_ADD, sock, &evReg);
	}
}



void do_poll(int epfd)
{

	struct epoll_event event;
	struct epoll_event evReg;

	while (!SOCKET_SERVER.shut_server)
	{
		int numEvents = epoll_wait(epfd, &event, 1, -1);
		
		if (numEvents > 0)
		{
			connection_st* conn = (connection_st*)(event.data.ptr);
			if (conn->type == T_ACCEPT)
			{
				do_accept(conn);
			}
			else
			{
				if (event.events & EPOLLOUT)
				{
					if (handleWriteEvent(conn) == -1)
					{
						//closeConnection(conn->sock);
						Message msg(conn->sock, SOCKET_TYPE_CLOSE, NULL);
						conn->isclose = true;
						ServiceMgr::instance()->GetService(conn->service_handle)->Push(msg);
						continue;
					}
				}

				if (event.events & EPOLLIN) {
					if (handleReadEvent(conn) == -1)
					{
						//closeConnection(conn->sock);
						Message msg(conn->sock, SOCKET_TYPE_CLOSE, NULL);
						conn->isclose = true;
						ServiceMgr::instance()->GetService(conn->service_handle)->Push(msg);
						continue;
					}
				}
				// TODO 这块是否这样处理？
				if (event.events & (EPOLLERR | EPOLLHUP | EPOLLRDHUP))
				{
					printf("epoll error ! %d\n", event.events);
					Message msg(conn->sock, SOCKET_TYPE_CLOSE, NULL);
					conn->isclose = true;
					ServiceMgr::instance()->GetService(conn->service_handle)->Push(msg);
					continue;
				}

				evReg = event;
				evReg.events = EPOLLIN | EPOLLONESHOT;
				if (conn->wbuf) evReg.events |= EPOLLOUT;
				//evReg.data.fd = sock;
				evReg.data.ptr = conn;
				epoll_ctl(epfd, EPOLL_CTL_MOD, conn->sock, &evReg);
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
Stream_Base* make_stream_packet(char *data, int len)
{
	int packet_len = sizeof(int)+len;
	Stream_Base* pts = new Stream_Base(packet_len);
	pts->write((char*)(&len), sizeof(int));
	pts->write(data, len);
	return pts;
}

int sendData(connection_st* conn, char *data, int len) 
{
	if (!conn->isclose)
	{
		Stream_Base* send_stream = make_stream_packet(data, len);

		if (conn->wbuf)
		{
			Stream_Base* last = conn->wbuf;
			while (last->next_)
			{
				last = last->next_;
			}
			last->next_ = send_stream;
		}
		else
		{
			int ret = write(conn->sock, send_stream->get_read_ptr(), send_stream->get_readable());

			if (ret > 0)
			{
				if (ret == send_stream->get_readable())
				{
					delete send_stream;
					return 0;
				}
				int left = len - ret;
				send_stream->move_read_pos(ret);

				conn->wbuf = send_stream;
				struct epoll_event evReg;
				evReg.events = EPOLLIN | EPOLLOUT | EPOLLONESHOT;
				evReg.data.ptr = conn;
				epoll_ctl(SOCKET_SERVER.epfd[conn->epfd], EPOLL_CTL_MOD, conn->sock, &evReg);
			}
			else
			{
				printf("send errno %d \n", errno);
				if (errno != EINTR && errno != EAGAIN)
				{
					printf("send errno %d \n", errno);
					return -1;
				}

				conn->wbuf = send_stream;

				struct epoll_event evReg;
				evReg.events = EPOLLIN | EPOLLOUT | EPOLLONESHOT;
				evReg.data.ptr = conn;
				epoll_ctl(SOCKET_SERVER.epfd[conn->epfd], EPOLL_CTL_MOD, conn->sock, &evReg);

			}
		}
	}
		
	return 0;
}


bool parse_stream_head(int fd, Stream_Base& stream, std::vector<Message>& vstream)
{
	while (1)
	{
		int  head_size = 4;
		int  data_len = *((int*)(stream.get_read_ptr()));
		int  packet_len = head_size + data_len;
		if (!data_len || packet_len > 1024 * 1024) 
		{
			return false;
		}

		if (stream.get_readable() >= packet_len)
		{
			stream.move_read_pos(head_size);

			Stream_Base* hstream = new Stream_Base(data_len);
			Message msg(fd, SOCKET_TYPE_DATA, hstream);
			int ir = hstream->write(stream.get_read_ptr(), data_len);
			if (ir == -1)
			{
				return false;
			}

			stream.move_read_pos(data_len);

			vstream.push_back(msg);
			if (stream.get_readable() < head_size)
			{
				if (stream.get_readable() == 0)
				{
					stream.reset_all();
				}
				else
				{
					int read_len = stream.get_readable();
					memcpy(stream.get_base_ptr(), stream.get_read_ptr(), read_len);
					stream.reset_all();
					stream.move_write_pos(read_len);
				}
				break;
			}
		}
		else
		{
			if (stream.get_read_ptr() != stream.get_base_ptr())
			{
				int read_len = stream.get_readable();
				memcpy(stream.get_base_ptr(), stream.get_read_ptr(), read_len);
				stream.reset_all();
				stream.move_write_pos(read_len);
			}
			break;
		}
	}
	return true;
}



int handleReadEvent(connection_st* conn) 
{
	if (!conn) 
    {
		return -1;
	}

	int ret = read(conn->sock, conn->rbuf->get_write_ptr(), conn->rbuf->get_space());
	if (ret>0)
	{
		conn->rbuf->move_write_pos(ret);
		if (conn->rbuf->get_readable() > 4)
		{
			std::vector<Message>   vstream;
			parse_stream_head(conn->sock, *conn->rbuf, vstream);
			
			for (std::vector<Message>::iterator iter = vstream.begin(); iter != vstream.end(); ++iter)
			{
				// 将拆好的包放到对应服务的队列中
				ServiceMgr::instance()->GetService(conn->service_handle)->Push(*iter);
				//__sync_add_and_fetch(&RecvNums, 1);
			}
            
            vstream.clear();
		}
	}
    // skynet -- socket_server.c : 1004
	else if (ret == 0) 
	{
		printf("handleReadEvent ret 0  %d \n", conn->sock);
		return -1;
	}
	else 
	{
		if (errno != EINTR && errno != EAGAIN) 
		{
            printf("handleReadEvent errno %d \n", errno);
			return -1;
		}
		else
		{
			return -1;
		}
	}

	return 0;
}

int handleWriteEvent(connection_st* conn) 
{
	if (conn->wbuf == NULL)
	{
		return 0;
	}


	while (conn->wbuf)
	{
		int ret = write(conn->sock, conn->wbuf->get_read_ptr(), conn->wbuf->get_readable());
		if (ret == -1)
		{
			if (errno != EINTR && errno != EAGAIN) {
                printf("handleWriteEvent errno %d \n",errno);
				return -1;
			}
			struct epoll_event evReg;
			evReg.events = EPOLLIN | EPOLLOUT | EPOLLONESHOT;
			evReg.data.ptr = conn;
			epoll_ctl(SOCKET_SERVER.epfd[conn->epfd], EPOLL_CTL_MOD, conn->sock, &evReg);
			break;
		}
		else
		{
			conn->wbuf->move_read_pos(ret);
			if (conn->wbuf->get_readable() > 0)
			{
				struct epoll_event evReg;
				evReg.events = EPOLLIN | EPOLLOUT | EPOLLONESHOT;
				evReg.data.ptr = conn;
				epoll_ctl(SOCKET_SERVER.epfd[conn->epfd], EPOLL_CTL_MOD, conn->sock, &evReg);
			}
			else
			{
				Stream_Base* tmpp = conn->wbuf;
				conn->wbuf = conn->wbuf->next_;
				delete tmpp;
				continue;
			}
		}
	}

	return 0;
}

void closeConnection(int fd)
{
	if (SOCKET_SERVER.slot[fd])
	{
		printf("closeConnection %d\n",fd);
		connection_st* conn = SOCKET_SERVER.slot[fd];
		SOCKET_SERVER.slot[fd] = NULL;
		struct epoll_event evReg;

		if (conn->rbuf)
		{
			delete conn->rbuf;
			conn->rbuf = NULL;
		}


		while (conn->wbuf)
		{
			Stream_Base* ptmp = conn->wbuf->next_;
			delete conn->wbuf;
			conn->wbuf = ptmp;
		}

		epoll_ctl(SOCKET_SERVER.epfd[conn->epfd], EPOLL_CTL_DEL, conn->sock, &evReg);
		close(conn->sock);
		Allocator_Manager::instance()->free((void*)(conn));

	}
    
}
