#!/bin/sh
# Starts the Driver Sleep Car web app on http://localhost:8000/web/
cd "$(dirname "$0")" || exit 1

if command -v python3 >/dev/null 2>&1; then
  PY=python3
elif command -v python >/dev/null 2>&1; then
  PY=python
else
  echo "Python 3 is needed to run the local web server."
  echo "Install it from https://www.python.org/downloads/"
  exit 1
fi

echo "Starting the web app at http://localhost:8000/web/"
echo "Keep this terminal open while you use the app. Press Ctrl+C to stop."
if command -v open >/dev/null 2>&1; then
  open "http://localhost:8000/web/"
elif command -v xdg-open >/dev/null 2>&1; then
  xdg-open "http://localhost:8000/web/"
fi
"$PY" -m http.server 8000
