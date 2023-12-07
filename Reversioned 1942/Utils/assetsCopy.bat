@echo off

echo Copying Assets

Set input="%~1Assets"
Set output="%~2Assets"



xcopy /y /i /s %input% %output%


echo Assets copied successfully
