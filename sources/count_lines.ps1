$extensions = @("*.c", "*.h")
$total = 0

foreach ($ext in $extensions) {
    $files = Get-ChildItem -Recurse -Include $ext
    $count = 0
    foreach ($file in $files) {
        $count += (Get-Content $file | Measure-Object -Line).Lines
    }
    Write-Host $ext ":" $count " lines"
    $total += $count
}
Write-Host "Result: $total lines"