This project implements a balance control system for a model drone designed to assist in remote healthcare delivery. The drone must maintain a stable horizontal position for 5 seconds while performing a thermal scan, simulating real-world autonomous medical support in challenging environments.

🎯 Project Objectives
Develop a closed-loop controller (Proportional or PID) to stabilize the drone.
Use sensor feedback from a potentiometer to measure angular displacement.
Control dual DC motors via H-Bridge drivers to correct orientation.
Provide visual feedback using LEDs for system status.
Output telemetry data via Serial for performance analysis.
Test and validate the system in both simulation (WokWi) and hardware (ReLOAD) environments.
🧰 System Components
Arduino Uno
Potentiometer (angle sensor)
2x DC Motors with H-Bridge controllers
LEDs (Green: Startup, Yellow: Scanning, Red: Shutdown)
Serial Monitor for telemetry output
🔧 Key Features
✅ Real-time control loop at 25Hz
✅ Proportional control (with optional PID extension)
✅ Motor signal mapping from control output
✅ Scan timer logic with LED indicators
✅ BlackBox telemetry logging in CSV format
