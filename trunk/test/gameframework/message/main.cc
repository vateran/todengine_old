#include <windows.h>
#include <MMSystem.h>
#include <hash_map>
#include <map>
#include <string>
#include <queue>

#pragma comment(lib, "winmm")

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
       만약 특정 Port 에 만 보내는 Message 라면, 해당 Port 에서만 이 메세지를
       참조하게 되고 나머지 Port 는 참조불가능 하게 한다.

       그럴려면 Message 가 보내질 Target Object 가 존재 해야만 한다. 

       class Message
            int tgtObjId;

       각 Object 는 ObjId 가 존재한다. 

       class Port
            void handleMessage(Message* msg)
            {
                // 어떤 처리
            }

            int id;

       class MessageServer
            void dispatch()
                // 현재 시간에 해당하는 모든 처리 가능한 Message 들을 뽑아 낸다.
                Messages(?) msgs = this->broadMsgQueue.pop(cur_time);

                // broadcast 메세지를 처리한다.
                for msg each msgs:
                    for port each this->ports;
                        if port.acceptMessage(msg)
                            port.handleMessage(msg);

                // send 메세지를 처리한다.
                Message msg = this->sendMesgQueue.pop(cur_time);
                Object port = this->port.find(msg.tgtObjId);
                if port.acceptMessage(msg)
                    port.handleMessage(msg);               

            Ports ports;
            MessageQueue broadMsgQueue;
            MessageQueue sendMsgQueue;
       
       이렇게 되면 각 Port 가 특정 메세지를 처리할 수 있게 되겠다.
       이 상태에서 모든 Object 가 Port 는 포함하던지, 아니면 상속을 받던지한다면
       어떠한 객체라도 메세지를 받게 된다.

       Minky 에서 예를 들면 프로젝트 후반에 캐릭터 선택하는 데서 어떤 처리를
       다른 모듈에 던지고 싶었다. 그럼 이런 현상이 발생한다.

       class CharacterSelectHandler
            void onSelectedCharacter()
                // 기존에 연관된 클래스 모듈
                prevObj->onSelectedCharacter()

                // 프로젝트 후반부에 연관된 클래스 모듈
                curObj->onSelectedCharacter()

                // 나중에 연관될 클래스 모듈들.
                // 계속 추가됨

        이런 상황에서 보통 제시 되는 해결책은 Publisher/Subscriber 패턴을
        이용해서 처리하게 리팩토링하는 것이다. 하지만 말이 쉽지
        Publisher/Subscriber 를 각 클래스마다 만드는것은 정말 짜증나고
        반복적인 작업인 것이다. 이 경우, Publisher/Subscriber 패턴을 아키텍쳐
        차원으로 녹여 버린 것이다. 

        class CharacterSelectHandler
            void onSelectedCharacter()
                SelectedCharacterMessage msg;
                msg.setCharacterIndex(index);
                MessageServer::instance().broadcastMessage(msg);

        class ProcessSelectedCharacter
            void handleMessage(Message msg)
                if (msg == SelectedCharacterMessage)
                    //처리
                    msg.getCharacterIndex()

        하지만 이것도 귀찮다. 프로젝트 진행할때마다 메세지가 기하 급수적으로
        늘어날 것이다. class SelectedCharacterMessage : public Message
        이런식으로 Message 를 상속받는 녀석이 굉장히 많아 진다.
        결국 이런걸 하고 싶다.

        class CharacterSelectHandler
            void onSelectedCharacter()
                Message msg;
                msg.param("index").setI(0);
                MessageServer::instance("SelectedCharacterMessage", msg);

        class ProcessSelectedCharacter
            void handleMessage(Message msg)
                if (msg == SelectedCharacterMessage)
                    // 처리
                    msg.param("index").getI() == 0;

        이러면 상속을 받지 않아도 되지만 parameter 를 처리하는데에
        추가적인 처리 비용이 발생한다. (귀찮음에 대한 대가 이다.)
        
        C++ 에서 제공하는 어떠한 compile-time 테크닉(meta programming, generic programming)
        을 통해서도 이 문제를 해결하긴 어렵다.
        C++ 은 동적인 언어가 아니기 때문이다. 이러한 동적언어의 특성을
        내장하는 python 이나 ruby 같은 언어는 어떨까? 결국 얘네들도
        객체의 속성을 Dictionary 형태로 관리할 수 밖에 없다. 그러므로 
        항상 추가적인 처리 비용이 따라 다닌다. 

        근본적인 생각을 해보자. Stored Program 형 컴퓨터 컨셉에서
        과연 이러한 동적인 프로그래밍이 가능할까?

        Stored Programm 컴퓨터 컨셉은 이렇다.

        메모리
        ----------------------------
        Program   <-------->   Data
                     처리
        ----------------------------

        메모리 안에 Program 과 Data 영역이 있지만 분리되어있는 형태이다.
        Program 은 Data 를 처리한다.

        CPU 의 ip(instruction pointer) 는 메모리에 있는 program(어셈블리 명령)
        을 한줄 한줄수행해 나간다. 그러다가 jmz 같은 명령을 만나면
        특정 위치로 ip 가 점프 하기도 한다. 

        어셈블리 명령 자체는 완전한 정적언어의 특성을 그대로 지니고 있다.
        caller 와 collee 는 완벽하게 약속되어진 방식으로 호출 할 수 있다.
        그리고 string based 인 paramter 는 꿈도 못꾼다. 
        만약 string based parameter 가 있다고 치자. 
        결국 string compare 가 있어야하고, 이러한 일이 CISC 컴퓨터가 아닌 이상
        string compare 하는 '프로그램'이 존재 해야하며, 이 작은 function 을
        call 해야 한다는 것을 의미한다.

        그러므로, RICS 컴퓨터에서 동적인 어떤 제어를 수행한다면, 그에 따르는
        추가적인 처리 비용은 발생한다. 

        
        Message Chain 의 개념 - override 에 관한 문제
            만약 특정 method 가 override 되었을때, 기본적인 처리를
            super class 의 method 에 위임하고 싶을 경우가 종종있다.
            pattern 을 사용한 좋은 해결책은 역시 template method 를 사용하는
            방법이긴 하지만, 이 경우, super class 의 메서드가 많이 질 수 있다는
            단점이 있다. 그리고, 보통 완전 새로운 기능이 추가되는 경우도 
            종종 있다.

        delay Message 의 개념
            Message 가 처리될 실제 시간은 지정하여 특정 처리를 지연시키는 기능이다.


*/

class Message
{
public:
    virtual~Message() {}
};

class TimeMessage : public Message
{
public:
    double time;
};

class Port
{
public:
    bool acceptMessage(Message* msg) const
    {
        return true;
    }
    void handleMessage(Message* msg)
    {
        TimeMessage* m = dynamic_cast<TimeMessage*>(msg);
        printf("%d : from [%f] cur[%f] \n", id, m->time,
            static_cast<double>(timeGetTime()) / 1000.0f);
    }

public:
    int id;
};


class PortServer
{
public:
    PortServer():idCounter(0)
    {

    }

    void add(Port* port)
    {
        port->id = idCounter++;
        this->ports.insert(Ports::value_type(port->id, port));
    }
    void remove(Port* port)
    {
        this->ports.erase(port->id);
    }

    void handleMessages()
    {
        double cur_time = getTime();
        
        while (this->msgQueue.size())
        {
            MsgSlot* s = &this->msgQueue.top();
            if (s->time < cur_time)
            {
                // broadcast message
                if (-1 == s->targetId)
                    broadcastSync(s->msg);
                else
                    sendSync(s->targetId, s->msg);

                this->msgQueue.pop();
            }
            else
                break;
        }
    }

    void handleMessage(int target_id, Message* msg)
    {
        Ports::iterator find_iter = this->ports.find(target_id);
        if (this->ports.end() == find_iter)
            return;
        if (find_iter->second->acceptMessage(msg))
            find_iter->second->handleMessage(msg);
    }

    void sendSync(int target_id, Message* msg)
    {
        handleMessage(target_id, msg);
    }
    void sendAsync(int target_id, Message* msg, double delay)
    {
        this->msgQueue.push(MsgSlot(target_id, msg, getTime() + delay));
    }
    void broadcastSync(Message* msg)
    {   
        for (Ports::iterator i = this->ports.begin();
             i != this->ports.end(); ++i)
        {
            if (i->second->acceptMessage(msg))
                i->second->handleMessage(msg);
        }
    }
    void broadcastAsync(Message* msg, double delay)
    {
        this->msgQueue.push(MsgSlot(-1, msg, getTime() + delay));
    }

    double getTime() const
    {
        return static_cast<double>(timeGetTime()) / 1000.0f;
    }

private:
    struct MsgSlot
    {
        MsgSlot(int target_id, Message* msg, double time):
            targetId(target_id), msg(msg), time(time) {}

        int targetId;
        Message* msg;
        double time;

        bool operator < (const MsgSlot& m) const
        {
            return this->time > m.time;
        }
    };

    typedef std::priority_queue<MsgSlot> MessageQueue;
    typedef stdext::hash_map<int, Port*> Ports;

private:
    MessageQueue msgQueue;
    Ports ports;

    int idCounter;

public:
    static PortServer  s_instance;
    static PortServer* instance() { return &s_instance; }
};
PortServer PortServer::s_instance;


//-----------------------------------------------------------------------------
int main()
{
    TimeMessage msg;
    Port port0;
    Port port1;

    PortServer::instance()->add(&port0);
    PortServer::instance()->add(&port1);

    bool ks[256];
    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        if (GetAsyncKeyState(VK_LEFT) && !ks[VK_LEFT])
        {
            msg.time = PortServer::instance()->getTime();
            printf ("Send [%f]\n", msg.time);
            PortServer::instance()->sendAsync(0, &msg, 5);
            ks[VK_LEFT] = true;
        }
        else if (GetAsyncKeyState(VK_RIGHT) && !ks[VK_RIGHT])
        {
            msg.time = PortServer::instance()->getTime();
            printf ("Send [%f]\n", msg.time);
            PortServer::instance()->sendSync(0, &msg);            
            ks[VK_RIGHT] = true;
        }
        else if (GetAsyncKeyState(VK_UP) && !ks[VK_UP])
        {
            msg.time = PortServer::instance()->getTime();
            printf ("Send [%f]\n", msg.time);
            PortServer::instance()->broadcastAsync(&msg, 5);
            ks[VK_UP] = true;
        }
        else if (GetAsyncKeyState(VK_DOWN) && !ks[VK_DOWN])
        {
            msg.time = PortServer::instance()->getTime();
            printf ("Send [%f]\n", msg.time);
            PortServer::instance()->broadcastSync(&msg);
            ks[VK_DOWN] = true;
        }

        if (!GetAsyncKeyState(VK_LEFT))
            ks[VK_LEFT] = false;
        if (!GetAsyncKeyState(VK_RIGHT))
            ks[VK_RIGHT] = false;
        if (!GetAsyncKeyState(VK_UP))
            ks[VK_UP] = false;
        if (!GetAsyncKeyState(VK_DOWN))
            ks[VK_DOWN] = false;

        PortServer::instance()->handleMessages();
    }

    return 0;
}
