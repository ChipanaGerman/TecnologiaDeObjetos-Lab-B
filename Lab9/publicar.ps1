# Ejecutar en una terminal normal: .\Lab9\publicar.ps1
# Crea commits con ambas identidades proporcionadas por el equipo y publica sin force.
$ErrorActionPreference = 'Stop'
$repoPath = Split-Path -Parent $PSScriptRoot
Set-Location -LiteralPath $repoPath
function Invoke-Git {
    param([Parameter(ValueFromRemainingArguments = $true)][string[]]$GitArgs)
    & git -c "safe.directory=$($repoPath.Replace('\','/'))" @GitArgs
    if ($LASTEXITCODE -ne 0) { throw "Git fallo: $($GitArgs -join ' ')" }
}
$staged = @(Invoke-Git diff --cached --name-only)
if ($staged.Count -gt 0) { throw 'Hay archivos preparados previamente. Revisarlos antes de publicar Lab9.' }
Invoke-Git add -- Lab9/.gitignore Lab9/CMakeLists.txt Lab9/src Lab9/tests Lab9/datos
Invoke-Git -c 'user.name=German Arturo Chipana Jeronimo' -c 'user.email=gchipanaj@unsa.edu.pe' commit -m 'Lab9: implementar MVC, Factory Method, Adapter y pruebas sin GUI'
$implementacion = Invoke-Git rev-parse HEAD
Invoke-Git add -- Lab9/README.md Lab9/INFORME.md Lab9/INFORME_LAB09_Chipana_Baca.pdf Lab9/diagramas Lab9/comparacion Lab9/evidencias 'Lab9/Guias_Practica 09_TEO.pdf' Lab9/publicar.ps1
Invoke-Git -c 'user.name=Leonardo Baca Calsin' -c 'user.email=lbacac@unsa.edu.pe' commit -m 'Lab9: documentar patrones, metricas, diagramas y demostracion'
$evaluado = Invoke-Git rev-parse HEAD
@"
# Identificacion de la entrega Lab9

Fecha: 18/11/2026.

Implementacion: https://github.com/ChipanaGerman/TecnologiaDeObjetos-Lab-B/commit/$implementacion

Commit evaluado (aplicacion, pruebas, informe y evidencias): https://github.com/ChipanaGerman/TecnologiaDeObjetos-Lab-B/commit/$evaluado

El commit posterior solo agrega este registro de identificacion.
"@ | Set-Content -LiteralPath (Join-Path $PSScriptRoot 'ENTREGA.md') -Encoding utf8
Invoke-Git add -- Lab9/ENTREGA.md
Invoke-Git -c 'user.name=German Arturo Chipana Jeronimo' -c 'user.email=gchipanaj@unsa.edu.pe' commit -m 'Lab9: registrar URL del commit evaluado'
Invoke-Git push origin HEAD
Write-Host "Publicacion completada. Commit evaluado: $evaluado"
