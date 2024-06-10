#include "GameChannel.h"
#include "GameMsg.h"
#include <iostream>
int main()
{
	ZinxKernel::ZinxKernelInit();
	ZinxKernel::Zinx_Add_Channel(*(new ZinxTCPListen(8899,new GameTcpFact())));
	ZinxKernel::Zinx_Run();
	ZinxKernel::ZinxKernelFini();
}