#include "bfconfig.hpp"
class DebuggerRunPointer
{
public:
    explicit DebuggerRunPointer(RunnerPointer *dbgobj) : runner(dbgobj),fail(false) {
        stat=DebugStatus::normal;
    }
    enum class Watchstrategy
    {
        readwatch=0,
        writewatch=1,
        readwrite=2,
        nonewatch=3
    };
    enum class DebugStatus
    {
        normal=0,
        error=1,
        finish=2,
        breakpoint=3
    };
    struct WatchedMem
    {
        int cellCode;
        Watchstrategy strategy;
    };
    bool failed() const
    { return fail; }
    bool addBreakpoint(size_t bp);
    bool cancelBreakpoint(size_t indx);
    bool addWatchmemory(size_t wp,Watchstrategy strat=Watchstrategy::nonewatch);
    bool cancelWatchmemory(size_t indx);
    void showStatus();
    void printHex08(size_t num);
    void printHex02(size_t num);
    int runSingleStep();
    int runContinue();
    int checkStatus(int retval);
private:
    RunnerPointer *runner;
    std::vector<size_t> breakpoint{};
    std::vector<WatchedMem> memWatch{};
    DebugStatus stat;
    bool fail;
};
using CommandHandler=std::function<void(DebuggerRunPointer&,
    const std::vector<std::string>&)>;
extern std::map<std::string,CommandHandler> commandTable;