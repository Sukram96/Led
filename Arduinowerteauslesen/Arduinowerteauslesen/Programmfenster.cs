using System.Threading;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;


namespace LedSteuerung
{
   public static class Programmfenster
    {
        [System.Runtime.InteropServices.DllImport("user32.dll")]
        static extern void mouse_event(int dwFlags, int dx, int dy, int dwData, int dwExtraInfo);
        public static void Nachrichtzuweisen(string Nachricht)
        {
            Nachricht = Nachricht.Remove(0, Nachricht.IndexOf("r") + 1);
            switch (Nachricht)
            {
                case "Musik":
                    System.Diagnostics.Process.Start("wmplayer.exe");
                    Thread.Sleep(700);
                    LeftClick(1200, 170);
                    Thread.Sleep(700);
                    SendKeys.SendWait("Bigfoot");
                    Thread.Sleep(600);
                    LeftClick(720, 240);
                    LeftClick(720, 240);
                    break;
                default:
                    break;
            }
        }
        public enum MouseActionAdresses
        {
            LEFTDOWN = 0x00000002,
            LEFTUP = 0x00000004,
            MIDDLEDOWN = 0x00000020,
            MIDDLEUP = 0x00000040,
            MOVE = 0x00000001,
            ABSOLUTE = 0x00008000,
            RIGHTDOWN = 0x00000008,
            RIGHTUP = 0x00000010
        }
        public static void LeftClick(int x, int y)
        {

            System.Windows.Forms.Cursor.Position = new Point(x, y);

            System.Windows.Forms.Cursor.Position = new Point(x, y);
            mouse_event((int)(MouseActionAdresses.LEFTDOWN), 0, 0, 0, 0);
            mouse_event((int)(MouseActionAdresses.LEFTUP), 0, 0, 0, 0);

        }
        public static void MoveCursor(int x, int y)
        {

            System.Windows.Forms.Cursor.Position = new Point(x, y);
        }

    }
}
