param([string]$Exe, [string[]]$ArgList, [string]$OutPrefix, [int[]]$AtMs)
Add-Type -AssemblyName System.Drawing
Add-Type @"
using System; using System.Text; using System.Runtime.InteropServices; using System.Collections.Generic;
public class W {
  [StructLayout(LayoutKind.Sequential)] public struct R { public int L, T, Ri, B; }
  public delegate bool EnumProc(IntPtr h, IntPtr l);
  [DllImport("user32.dll")] public static extern bool EnumWindows(EnumProc f, IntPtr l);
  [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("user32.dll")] public static extern int GetClassName(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
  [DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr h, out R r);
  [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
  [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr h, IntPtr dc, uint flags);
  public static IntPtr Find(uint pid) {
    IntPtr found = IntPtr.Zero;
    EnumWindows((h, l) => { uint p; GetWindowThreadProcessId(h, out p);
      var s = new StringBuilder(64); GetClassName(h, s, 64);
      if (p == pid && IsWindowVisible(h) && s.ToString().StartsWith("SDL")) { found = h; return false; }
      return true; }, IntPtr.Zero);
    return found; }
}
"@
[W]::SetProcessDPIAware() | Out-Null
$p = Start-Process -FilePath $Exe -ArgumentList $ArgList -PassThru
$start = Get-Date
$i = 0
foreach ($t in $AtMs) {
    while (((Get-Date) - $start).TotalMilliseconds -lt $t) { Start-Sleep -Milliseconds 50 }
    $h = [W]::Find([uint32]$p.Id)
    if ($h -eq [IntPtr]::Zero) { Write-Output "no window at $t"; continue }
    $r = New-Object W+R; [W]::GetClientRect($h, [ref]$r) | Out-Null
    $bmp = New-Object System.Drawing.Bitmap ([Math]::Max(1, $r.Ri - $r.L)), ([Math]::Max(1, $r.B - $r.T))
    $g = [System.Drawing.Graphics]::FromImage($bmp)
    $dc = $g.GetHdc(); [W]::PrintWindow($h, $dc, 3) | Out-Null; $g.ReleaseHdc($dc)
    $bmp.Save("$OutPrefix-$i.png")
    Write-Output "saved $OutPrefix-$i.png $($bmp.Width)x$($bmp.Height)"
    $i++
}
Stop-Process -Id $p.Id -Force
