# PowerShell script equivalent to cli.sh
# Usage: .\cli.ps1 [arguments...]

java -Xms8G -Xmx12G -jar build\shadow\lib-*.jar @args
