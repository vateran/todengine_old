#include <windows.h>
#include <hash_map>
#include <map>
#include <string>

/**
    1. 모든 Port 는 Message 를 조회해 볼 수 있다.
    2. 모든 Port 가 Message 를 조회해 볼 수 있기 때문에, 해당 tick 에 해당하는
       Message 를 Peek 해 볼 수 있다. 그러므로 이것으로 이벤트 처리가 가능하다.
    3. 내가 하고 싶은건, Network 로 부터 메세지를 받거나, 특정 이벤트가
       발생하면 그 이벤트를 감지할 수 있는 애들이 자동으로 그 통보를 받았으면
       한다. 이런일이 자주 발생한다. 완전히 분리된, 시스템에서
       특정 메세지를 감지해서 처리할 일이 종종 벌어진다.

       예를 들면, 코드의 특정 위치에서 어떤 이벤트를 일으키고 싶다면,
       그 특정위치에서 Message 를 발생시킨다.

       마우스로 특정 버튼을 클릭(MouseLClickMessage) 를 발생시키는
       객체를 만들어 보자ㅡ

    class InputServer
        void update()
            if Mouse.IsClicked():
                PortManager::instance().broadcaseSync(MouseLClickMessage);

       InputServer 는 마우스 입력을 감지하여 MouseLClickMessage 를 전 Port 에
       broadcast 한다. MouseLClickMessage 는 현재 tick 동안은 Port 들이
       global Message Queue 를 참조 할 수 있다. 현재 tick 동안은 
       MouseLClickMessage 가 계속 남아 있다. 하지만 다음 tick 에서는 사라진다.
       만약 특정 Port 에 만 보내는 Message 라면, 해당 Port 만 


*/

class Port
{
public:
};


class PortServer
{
public:
    void update();
};


class Message
{
public:
};

//-----------------------------------------------------------------------------
int main()
{
    return 0;
}

