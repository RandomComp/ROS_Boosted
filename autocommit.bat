@echo off

git add -A
git commit -m "Autocommit: %DATE% %TIME%"
git push origin main

exit