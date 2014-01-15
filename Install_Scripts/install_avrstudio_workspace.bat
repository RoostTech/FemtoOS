@echo off

if exist Install_Scripts (echo === Making studioprojects) else (echo Start me in the FemtoOS_[version] directory of the Femto OS distribution, with: & echo Install_Scripts\create_avrstudio_workspace & goto END)

mkdir  IDE\studioprojects 2>NUL
echo === Making demo projects
call Install_Scripts\create_avrstudio_project.bat Remember
call Install_Scripts\create_avrstudio_project.bat Interrupt
call Install_Scripts\create_avrstudio_project.bat Queus
call Install_Scripts\create_avrstudio_project.bat Shell
call Install_Scripts\create_avrstudio_project.bat Bare
call Install_Scripts\create_avrstudio_project.bat FlashLeds
call Install_Scripts\create_avrstudio_project.bat Hooks
call Install_Scripts\create_avrstudio_project.bat Minimal
call Install_Scripts\create_avrstudio_project.bat Rendezvous
call Install_Scripts\create_avrstudio_project.bat Sleep
call Install_Scripts\create_avrstudio_project.bat Watchdog
call Install_Scripts\create_avrstudio_project.bat Passon
call Install_Scripts\create_avrstudio_project.bat HelloWorld
echo === Done

:END
