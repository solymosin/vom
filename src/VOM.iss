; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "VOM"
#define MyAppVersion "0.97"
#define MyAppPublisher "Solymosi Norbert"
#define MyAppURL "http://www.univet.hu/"
#define MyAppExeName "VOM.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{A7A0D0CB-DD2E-4542-ACF4-B7BA2F64F663}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
LicenseFile=C:\vom\arch\GPL3.rtf
OutputDir=C:\vom\arch
OutputBaseFilename=VOM_setup
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "hungarian"; MessagesFile: "compiler:Languages\Hungarian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "C:\vom\build-VOM-Desktop_Qt_5_3_MinGW_32bit-Release\release\VOM.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\vom\src\db.sqlite"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\vom\src\VOM.ico"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\vom\arch\GPL3.rtf"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt5\5.3\mingw482_32\bin\Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt5\5.3\mingw482_32\bin\Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt5\5.3\mingw482_32\bin\Qt5Sql.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt5\5.3\mingw482_32\bin\Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt5\5.3\mingw482_32\bin\Qt5PrintSupport.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt5\5.3\mingw482_32\bin\icudt52.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt5\5.3\mingw482_32\bin\icuin52.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt5\5.3\mingw482_32\bin\icuuc52.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt5\5.3\mingw482_32\bin\libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt5\5.3\mingw482_32\bin\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt5\5.3\mingw482_32\bin\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Qt5\5.3\mingw482_32\plugins\platforms\qwindows.dll"; DestDir: "{app}\platforms"; Flags: ignoreversion
Source: "C:\Qt5\5.3\mingw482_32\plugins\imageformats\qjpeg.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "C:\Qt5\5.3\mingw482_32\plugins\imageformats\qtiff.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "C:\Qt5\5.3\mingw482_32\plugins\sqldrivers\qsqlite.dll"; DestDir: "{app}\sqldrivers"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

