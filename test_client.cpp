#define LOG_TAG "HelloService"
#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>
#include <utils/Log.h>
#include "IHelloService.h"

using namespace android;

/* ./test_client hello
 * ./test_client hello <name>
 */
int main(int argc, char **argv)
{
    int cnt;
    
    if (argc < 2){
        printf("Usage:\n");
        printf("%s hello\n", argv[0]);
        printf("%s hello <name>\n", argv[0]);
        return -1;
    }

    /* getService */
    /* 打开驱动, mmap */
    sp<ProcessState> proc(ProcessState::self());

    /* 获得BpServiceManager */
    sp<IServiceManager> sm = defaultServiceManager();
    //获取hello服务
    sp<IBinder> binder = sm->getService(String16("hello"));

    if (binder == 0)
    {
        printf("can't get hello service\n");
        return -1;
    }

    /* service肯定是BpHelloServie指针 */
    sp<IHelloService> service = interface_cast<IHelloService>(binder);

    /* 调用Service的函数 */
    if (argc < 3) {
        service->sayhello();
        printf("client call sayhello");
    }
    else {
        cnt = service->sayhello_to(argv[2]);
        printf("client call sayhello_to, cnt = %d", cnt);
    }
    
    return 0;
}
