# Function to run the processes
function RunProcesses {
    # Start the server process
    # countryCount, producersCount, consumersCount, deltaT, sendFiles
    $s = Start-Process -FilePath ".\Server.exe" -ArgumentList "5 4 2 1 0" -PassThru -WindowStyle Normal

    # Wait for 0.1 seconds
    Start-Sleep -Seconds 0.1

	#-WindowStyle Normal
    # Start client processes in separate windows
    # clientId, deltaX, sendFiles
    $c0 = Start-Process -FilePath ".\Client.exe" -ArgumentList "0 2000 0" -PassThru -WindowStyle Normal
    $c1 = Start-Process -FilePath ".\Client.exe" -ArgumentList "1 2000 0" -PassThru -WindowStyle Normal
    $c2 = Start-Process -FilePath ".\Client.exe" -ArgumentList "2 2000 0" -PassThru -WindowStyle Normal
    $c3 = Start-Process -FilePath ".\Client.exe" -ArgumentList "3 2000 0" -PassThru -WindowStyle Normal
    $c4 = Start-Process -FilePath ".\Client.exe" -ArgumentList "4 2000 0" -PassThru -WindowStyle Normal

    # Wait for all processes to finish
    $s | Wait-Process
    $c0, $c1, $c2, $c3, $c4 | Wait-Process
}

$averageExT = 0
# Run the processes 10 times
for ($i = 1; $i -le 1; $i++) {
    Write-Host "Run $i"
    $executionTime = Measure-Command {
        RunProcesses
    }
    $averageExT = $averageExT + $executionTime
    Write-Host "Execution Time for Run {$i}: $($executionTime.TotalSeconds) seconds`n"
}
# Calculate the average execution time in seconds
$iterations = 1
$averageExTInSeconds = $averageExT.TotalSeconds / $iterations

Write-Host "Average Execution Time per Iteration: $averageExTInSeconds seconds"
