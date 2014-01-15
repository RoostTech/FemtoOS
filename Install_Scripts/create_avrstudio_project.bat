@echo off

if exist Install_Scripts (echo === Creating project %1) else (echo Start me in the FemtoOS_[version] directory of the Femto OS distribution, with & echo .\Install_Scripts\create_avrstudio_project [project_name] & goto END)

mkdir        IDE\studioprojects\FemtoOS_%1 2>NUL
del /S/Q/F   IDE\studioprojects\FemtoOS_%1\* > NUL
mkdir        IDE\studioprojects\FemtoOS_%1\standard 2>NUL
mkdir        IDE\studioprojects\FemtoOS_%1\compact 2>NUL

copy         MainCode\demos_headers\config_Test%1.h IDE\studioprojects\FemtoOS_%1\config_application.h > NUL
copy         MainCode\demos_source\code_Test%1.c   IDE\studioprojects\FemtoOS_%1\code_Test%1.c > NUL

type         Install_Scripts\avrstudio\project_template | Install_Scripts\strrep.exe XXXXX %1 > IDE\studioprojects\FemtoOS_%1\project_Test%1.aps

:END