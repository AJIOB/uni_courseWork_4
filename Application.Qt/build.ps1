param (
    # [string]$isClean = "false",
    [string]$configuration = "Release",
    [string]$platform = "win32",
    [string]$QTDIR = "C:\Qt\Qt5.7.1\5.7\msvc2015"
 )

function buildOneProject ([string]$projectName) {
  & msbuild $projectName\$projectName.vcxproj /p:configuration=$configuration /p:platform=$platform /Property:SolutionDir=$pwd\ /Property:QTDIR=$QTDIR
  if ($LastExitCode -ne 0)
  {
    exit $LastExitCode
  }
}

# if ($isClean -eq "false")
# {
#   $param = /p:configuration=$configuration /p:platform=$platform
#   echo "part 1"
# } else {
#   # $param = /t:clean
#   echo "part 2" 
# }

buildOneProject Logger
buildOneProject HashFuncs
buildOneProject Configuration
# buildOneProject ClassHierarchy
