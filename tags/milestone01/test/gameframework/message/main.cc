#include <windows.h>
#include <MMSystem.h>
#include <hash_map>
#include <map>
#include <string>
#include <queue>

#pragma comment(lib, "winmm")

/**
    1. ��� Port �� Message �� ��ȸ�� �� �� �ִ�.
    2. ��� Port �� Message �� ��ȸ�� �� �� �ֱ� ������, �ش� tick �� �ش��ϴ�
       Message �� Peek �� �� �� �ִ�. �׷��Ƿ� �̰����� �̺�Ʈ ó���� �����ϴ�.
    3. ���� �ϰ� ������, Network �� ���� �޼����� �ްų�, Ư�� �̺�Ʈ��
       �߻��ϸ� �� �̺�Ʈ�� ������ �� �ִ� �ֵ��� �ڵ����� �� �뺸�� �޾�����
       �Ѵ�. �̷����� ���� �߻��Ѵ�. ������ �и���, �ý��ۿ���
       Ư�� �޼����� �����ؼ� ó���� ���� ���� ��������.

       ���� ���, �ڵ��� Ư�� ��ġ���� � �̺�Ʈ�� ����Ű�� �ʹٸ�,
       �� Ư����ġ���� Message �� �߻���Ų��.

       ���콺�� Ư�� ��ư�� Ŭ��(MouseLClickMessage) �� �߻���Ű��
       ��ü�� ����� ���ڤ�

    class InputServer
        void update()
            if Mouse.IsClicked():
                PortManager::instance().broadcaseSync(MouseLClickMessage);

       InputServer �� ���콺 �Է��� �����Ͽ� MouseLClickMessage �� �� Port ��
       broadcast �Ѵ�. MouseLClickMessage �� ���� tick ������ Port ����
       global Message Queue �� ���� �� �� �ִ�. ���� tick ������ 
       MouseLClickMessage �� ��� ���� �ִ�. ������ ���� tick ������ �������.
       ���� Ư�� Port �� �� ������ Message ���, �ش� Port ������ �� �޼�����
       �����ϰ� �ǰ� ������ Port �� �����Ұ��� �ϰ� �Ѵ�.

       �׷����� Message �� ������ Target Object �� ���� �ؾ߸� �Ѵ�. 

       class Message
            int tgtObjId;

       �� Object �� ObjId �� �����Ѵ�. 

       class Port
            void handleMessage(Message* msg)
            {
                // � ó��
            }

            int id;

       class MessageServer
            void dispatch()
                // ���� �ð��� �ش��ϴ� ��� ó�� ������ Message ���� �̾� ����.
                Messages(?) msgs = this->broadMsgQueue.pop(cur_time);

                // broadcast �޼����� ó���Ѵ�.
                for msg each msgs:
                    for port each this->ports;
                        if port.acceptMessage(msg)
                            port.handleMessage(msg);

                // send �޼����� ó���Ѵ�.
                Message msg = this->sendMesgQueue.pop(cur_time);
                Object port = this->port.find(msg.tgtObjId);
                if port.acceptMessage(msg)
                    port.handleMessage(msg);               

            Ports ports;
            MessageQueue broadMsgQueue;
            MessageQueue sendMsgQueue;
       
       �̷��� �Ǹ� �� Port �� Ư�� �޼����� ó���� �� �ְ� �ǰڴ�.
       �� ���¿��� ��� Object �� Port �� �����ϴ���, �ƴϸ� ����� �޴����Ѵٸ�
       ��� ��ü�� �޼����� �ް� �ȴ�.

       Minky ���� ���� ��� ������Ʈ �Ĺݿ� ĳ���� �����ϴ� ���� � ó����
       �ٸ� ��⿡ ������ �;���. �׷� �̷� ������ �߻��Ѵ�.

       class CharacterSelectHandler
            void onSelectedCharacter()
                // ������ ������ Ŭ���� ���
                prevObj->onSelectedCharacter()

                // ������Ʈ �Ĺݺο� ������ Ŭ���� ���
                curObj->onSelectedCharacter()

                // ���߿� ������ Ŭ���� ����.
                // ��� �߰���

        �̷� ��Ȳ���� ���� ���� �Ǵ� �ذ�å�� Publisher/Subscriber ������
        �̿��ؼ� ó���ϰ� �����丵�ϴ� ���̴�. ������ ���� ����
        Publisher/Subscriber �� �� Ŭ�������� ����°��� ���� ¥������
        �ݺ����� �۾��� ���̴�. �� ���, Publisher/Subscriber ������ ��Ű����
        �������� �쿩 ���� ���̴�. 

        class CharacterSelectHandler
            void onSelectedCharacter()
                SelectedCharacterMessage msg;
                msg.setCharacterIndex(index);
                MessageServer::instance().broadcastMessage(msg);

        class ProcessSelectedCharacter
            void handleMessage(Message msg)
                if (msg == SelectedCharacterMessage)
                    //ó��
                    msg.getCharacterIndex()

        ������ �̰͵� ������. ������Ʈ �����Ҷ����� �޼����� ���� �޼�������
        �þ ���̴�. class SelectedCharacterMessage : public Message
        �̷������� Message �� ��ӹ޴� �༮�� ������ ���� ����.
        �ᱹ �̷��� �ϰ� �ʹ�.

        class CharacterSelectHandler
            void onSelectedCharacter()
                Message msg;
                msg.param("index").setI(0);
                MessageServer::instance("SelectedCharacterMessage", msg);

        class ProcessSelectedCharacter
            void handleMessage(Message msg)
                if (msg == SelectedCharacterMessage)
                    // ó��
                    msg.param("index").getI() == 0;

        �̷��� ����� ���� �ʾƵ� ������ parameter �� ó���ϴµ���
        �߰����� ó�� ����� �߻��Ѵ�. (�������� ���� �밡 �̴�.)
        
        C++ ���� �����ϴ� ��� compile-time ��ũ��(meta programming, generic programming)
        �� ���ؼ��� �� ������ �ذ��ϱ� ��ƴ�.
        C++ �� ������ �� �ƴϱ� �����̴�. �̷��� ��������� Ư����
        �����ϴ� python �̳� ruby ���� ���� ���? �ᱹ ��׵鵵
        ��ü�� �Ӽ��� Dictionary ���·� ������ �� �ۿ� ����. �׷��Ƿ� 
        �׻� �߰����� ó�� ����� ���� �ٴѴ�. 

        �ٺ����� ������ �غ���. Stored Program �� ��ǻ�� ��������
        ���� �̷��� ������ ���α׷����� �����ұ�?

        Stored Programm ��ǻ�� ������ �̷���.

        �޸�
        ----------------------------
        Program   <-------->   Data
                     ó��
        ----------------------------

        �޸� �ȿ� Program �� Data ������ ������ �и��Ǿ��ִ� �����̴�.
        Program �� Data �� ó���Ѵ�.

        CPU �� ip(instruction pointer) �� �޸𸮿� �ִ� program(����� ���)
        �� ���� ���ټ����� ������. �׷��ٰ� jmz ���� ����� ������
        Ư�� ��ġ�� ip �� ���� �ϱ⵵ �Ѵ�. 

        ����� ��� ��ü�� ������ ��������� Ư���� �״�� ���ϰ� �ִ�.
        caller �� collee �� �Ϻ��ϰ� ��ӵǾ��� ������� ȣ�� �� �� �ִ�.
        �׸��� string based �� paramter �� �޵� ���۴�. 
        ���� string based parameter �� �ִٰ� ġ��. 
        �ᱹ string compare �� �־���ϰ�, �̷��� ���� CISC ��ǻ�Ͱ� �ƴ� �̻�
        string compare �ϴ� '���α׷�'�� ���� �ؾ��ϸ�, �� ���� function ��
        call �ؾ� �Ѵٴ� ���� �ǹ��Ѵ�.

        �׷��Ƿ�, RICS ��ǻ�Ϳ��� ������ � ��� �����Ѵٸ�, �׿� ������
        �߰����� ó�� ����� �߻��Ѵ�. 

        
        Message Chain �� ���� - override �� ���� ����
            ���� Ư�� method �� override �Ǿ�����, �⺻���� ó����
            super class �� method �� �����ϰ� ���� ��찡 �����ִ�.
            pattern �� ����� ���� �ذ�å�� ���� template method �� ����ϴ�
            ����̱� ������, �� ���, super class �� �޼��尡 ���� �� �� �ִٴ�
            ������ �ִ�. �׸���, ���� ���� ���ο� ����� �߰��Ǵ� ��쵵 
            ���� �ִ�.

        delay Message �� ����
            Message �� ó���� ���� �ð��� �����Ͽ� Ư�� ó���� ������Ű�� ����̴�.


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
