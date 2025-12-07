@echo off

git add -A
git commit -m "Автокоммит: %DATE% %TIME%"
git push origin main

exit