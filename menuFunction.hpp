#ifndef MenuFunction_H
#define MenuFunction_H

// EtherTerm SVN: $Id$
// Source: $HeadURL$
// $LastChangedDate$
// $LastChangedRevision$
// $LastChangedBy$

#include <string>

typedef struct MenuRecord
{
    std::string MenuName;     // menu name
    std::string Directive;    // normal menu text file
    std::string MenuPrompt;   // menu prompt
    bool        Lightbar;     // Light-bar Menu?

} MenuRecord;

typedef struct CommandRecord
{
    std::string  LDesc;       // command description
    std::string  SDesc;       // command string
    std::string  CKeys;       // command execution keys
    std::string  CmdKeys;     // command keys
    std::string  MString;     // command data
    bool         LBarCmd;     // Is This a Light-bar Cmd
    std::string  HiString;    // Highlighted
    std::string  LoString;    // Un-highlighted
    uint16_t     Xcoord;      // Light-bar X coordinate
    uint16_t     Ycoord;      // Light-bar Y coordinate

} CommandRecord;


class MenuFunction
{
protected:

    MenuRecord     *menuRecord;
    CommandRecord  *commandRecord;
    int  numCommands;     // Number of Commands in Loaded Menu
    bool isSystemActive;  // System Exit

public:

    char MENUPATH[255];

    std::string _curmenu;  // Current Menu
    std::string _premenu;  // Previous Menu
    std::string _gosub;    // GoSub Menu.

    // Menu Light-bar Variables
    short xPosition;               // Holds X coordinate
    short yPosition;               // Holds Y coordinate
    short numLightbarCommand;      // Holds Light-bar # of choices
    short choice;                  // Holds Current Light-bar #

    short  *commandIndex;
    short  *commandIndexLightbar;

    unsigned long cntEscCmds;

    int  sequence, secondSequence;
    bool isEscapeSequence;       // Is Input key Escaped char, or Normal Key
    char outBuff[1024];          // Holds Formatted Light-bar Data
    std::string output;          // Buffer for writing all light-bars at the same time

    int commandsExecuted;        // Test's for hot keys commands executed, if non pass through loop
    int firstCommandsExecuted;   // If we executed all FIRSTCMD and nothing is left then return

    int currentSystem;           // Light-bar Starting Position for Interfaces.
    // This needs access from ie Title Scan Class.

    MenuFunction();
    ~MenuFunction();

    // Below here are Menu Processing Functions
    bool isLoadNewMenu;

    void dataParseHelper(std::string &temp);
    // Command Data Functions

    void commandsParse(std::string cfgdata, int idx);
    int  commandsExist(std::string MenuName, int idx);
    int  commandsCount(std::string MenuName);
    int  commandsReadData(std::string MenuName, int idx);

    // Menu Data Functions
    int  menuParseData(std::string cfgdata);
    int  menuReadData(std::string MenuName);

    // Read in / Load Menu and Commands
    void menuReadCommands();
    void menuReload();
    int  menuExists();
    void menuStart();
    void menuClearObjects();

    void menuLightBars(char *inPut);
    void menuProcess(char *mString, uint32_t area=0);

    // Menu Command Processing
    void menuDoCommands(CommandRecord *cmdr);

    // Menu System IO
    // ----------------------------------------------------------------------
    static void rightSpacing(char *str, int space);
    static void leftSpacing(char *str, int space);
    static void maskInput(char *str);
    static void inputField(char *text, int &len);


    static int  getKey();
    static void getLine(char *line,     // Returns Input into Line
                 int   length,          // Max Input Length of String
                 char *leadoff = 0,     // Data to Display in Default String {Optional}
                 int   hid     = false, // If input is Echoed as hidden      {Optional}
                 char *chlist = 0);     // Valid Input Char List             {Optional}

    static void ansiForegroundColor(char *data, int fg);
    static void ansiBackgroundColor(char *data, int bg);
    static void sequenceToAnsi(char* szString, int buffer=true);
    static void displayAnsiFile(std::string fileName);
};

# endif
