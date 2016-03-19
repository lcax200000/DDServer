# DDServer
c-lua server
使用epoll 通讯的逻辑放在lua的框架(也可以是c，只要是ServiceObj的子类即可)
消息队列使用boost的lock free，带内存池，服务配置在config.xml里
每个node是个物理节点，node 下的unit是一个lua服务，可以配置端口和起始执行文件并在lua里使用c_fun.dispatch_message
注册处理消息回调。
编译方式：在debug目录下  
cmake ..
make
