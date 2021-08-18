# <Program> Watchdog

## Summary
- C++ console app to run in background waiting on the program PID to exit.
- On exit, the watchdog attempts to close several applications/services.

## Usage
`$ <program>.exe <PID> <Log level> <Number of days to retain logs>`
- **PID**: Calling program's process ID to watch
- **Log level**: Level at which to log; *0-4*
- **Number of days to retain logs**: Application deletes anything older than *n* days from launching.

## Dependencies
- C++17

## Notes
- Watchdog needs to run at the same privilege level of the calling application to terminate the above applications, if they are started by the calling application.

# Run Phases

## Launch Phase
- On launch:
  - initialize logging
  - wait on PID for exit

## Exit Phase
- On exit:
  - terminate all above applications
  - finalize logging