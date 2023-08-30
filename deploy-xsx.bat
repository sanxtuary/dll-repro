@echo off

set engine_ver=5.2
set engine_dir=E:/UE_%engine_ver%
set archive_dir=D:\Build
set target=DynamicLinkRepro
set project_dir=E:\DynamicLinkRepro
set configuration=Development
set branch=develop

set target_platform=XSX
title (%target_platform%) %engine_ver% [%configuration%]
call "%engine_dir%\Engine\Build\BatchFiles\RunUAT.bat" BuildCookRun -project="%project_dir%\%target%.uproject" -nogit -nop4 -build -cook -stage -pak -package -allmaps -platform=%target_platform% -stage -config=%configuration% -archive -clientconfig=%configuration% -serverconfig=%configuration% -nosndbs -buildmachine -nocodesign -compressed -deploy -run
@REM -nocompileeditor
pause