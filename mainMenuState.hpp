#ifndef __MAINMENU_STATE__
#define __MAINMENU_STATE__

// EtherTerm SVN: $Id$
// Source: $HeadURL$
// $LastChangedDate$
// $LastChangedRevision$
// $LastChangedBy$

#include "termState.hpp"
#include "menuManager.hpp"

#include <iostream>
#include <string>
#include <vector>

/*
 * This Class Holds a connection to the MenuState -> SocketState -> Term
 * This is where we will initiate either Telnet or SSH
 */
class MainMenuState :
    public TermState, MenuManager
{
public:

    MainMenuState() :
        isActive(false)
    { }

    virtual ~MainMenuState()
    {
        std::cout << "Shutting Down MainMenuState" << std::endl;
    }
    virtual void update();
    virtual bool onEnter();
    virtual bool onExit();
    virtual std::string getStateID() const
    {
        return m_menuID;
    }

private:

    /*
        virtual void setCallbacks(const std::vector<Callback>& callbacks);
    */
    static void menuStartTelnet();
    static void menuStartSSH();
    static const std::string m_menuID;
    bool isActive;



};

#endif
