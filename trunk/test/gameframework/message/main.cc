#include <windows.h>
#include <hash_map>
#include <map>
#include <string>

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
       ���� Ư�� Port �� �� ������ Message ���, �ش� Port �� 


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

