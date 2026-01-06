#include <ncurses.h>
#include <unistd.h>
#include <stdbool.h>

#include "cpu.h"
#include "mem.h"
#include "swap.h"
#include "load.h"
#include "process.h"
#include "iowait.h"
#include "disk.h"
#include "context.h"
#include "interrupt.h"

WINDOW *headerWin;
WINDOW *tier1Win;
WINDOW *tier2Win;

void initUI()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int width = COLS;

    headerWin = newwin(3, width, 0, 0);   
    tier1Win  = newwin(8, width, 3, 0);   
    tier2Win  = newwin(8, width, 11, 0);  
    
    refresh(); 
}

void drawHeader()
{
    werase(headerWin); 
    box(headerWin, 0, 0);
    mvwprintw(headerWin, 1, 2, "LINUX SYSTEM MONITOR");
    wnoutrefresh(headerWin);
}

void drawTier1(double cpu, double mem, double swap,
               LoadAvg load, ProcessInfo p)
{
    werase(tier1Win);
    box(tier1Win, 0, 0);
    mvwprintw(tier1Win, 0, 2, " CORE HEALTH ");

    mvwprintw(tier1Win, 2, 2, "CPU Usage        : %6.2f %%", cpu);
    mvwprintw(tier1Win, 3, 2, "Memory Usage     : %6.2f %%", mem);
    mvwprintw(tier1Win, 4, 2, "Swap Usage       : %6.2f %%", swap);

    mvwprintw(tier1Win, 5, 2, "Load Avg (1/5/15): %.2f %.2f %.2f",
              load.one, load.five, load.fifteen);

    mvwprintw(tier1Win, 6, 2, "Processes        : %d running / %d total",
              p.running, p.total);

    wnoutrefresh(tier1Win); 
}

void drawTier2(double iowait, DiskIO disk, long long ctxt, long long intr)
{
    werase(tier2Win);
    box(tier2Win, 0, 0);
    mvwprintw(tier2Win, 0, 2, " TIER 2 BOTTLENECKS ");

    mvwprintw(tier2Win, 2, 2, "IO Wait          : %6.2f %%", iowait);
    mvwprintw(tier2Win, 3, 2, "Disk Read/Write  : %lld / %lld KB/s",
              disk.readKB, disk.writeKB);
    mvwprintw(tier2Win, 4, 2, "Context Switches : %lld /s", ctxt);
    mvwprintw(tier2Win, 5, 2, "Interrupts       : %lld /s", intr);

    wrefresh(tier2Win);
}

int main()
{
    initUI();
    drawHeader();

    CPUData prevCPU = readCPU();
    IOWaitData prevIO = readIOWait();
    DiskIO prevDisk = readDisk();
    long long prevCtxt = readContextSwitches();
    long long prevIntr = readInterrupts();

    nodelay(stdscr, TRUE);

    while (true)
    {
        int ch = getch();
        if (ch == 'q' || ch == 'Q')
            break;

        // ---------- TIER 1 ----------
        CPUData currCPU = readCPU();
        double cpu = calculateCPU(prevCPU, currCPU);
        double mem = getMemoryUsage();
        double swap = getSwapUsage();
        LoadAvg load = getLoadAverage();
        ProcessInfo p = getProcessInfo();

        // ---------- TIER 2 ----------
        IOWaitData currIO = readIOWait();
        double iowait = calculateIOWait(prevIO, currIO);

        DiskIO currDisk = readDisk();
        DiskIO diskRate = calcDiskRate(prevDisk, currDisk);

        long long ctxt = readContextSwitches();
        long long intr = readInterrupts();

        drawTier1(cpu, mem, swap, load, p);
        drawTier2(
            iowait,
            diskRate,
            ctxt - prevCtxt,
            intr - prevIntr
        );

        // ---------- UPDATE PREVIOUS ----------
        prevCPU = currCPU;
        prevIO = currIO;
        prevDisk = currDisk;
        prevCtxt = ctxt;
        prevIntr = intr;

        sleep(1);
    }

    endwin();
    return 0;
}
