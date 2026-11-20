@echo off
rem Starts the Driver Sleep Car web app on http://localhost:8000/web/
cd /d "%~dp0"

where python >nul 2>nul
if errorlevel 1 (
  echo Python 3 is needed to run the local web server.
  echo Install it from https://www.python.org/downloads/ and tick "Add python to PATH".
  pause
  exit /b 1
)

echo Starting the web app at http://localhost:8000/web/
echo Keep this window open while you use the app. Close it to stop the server.
start "" "http://localhost:8000/web/"
python -m http.server 8000
pause
