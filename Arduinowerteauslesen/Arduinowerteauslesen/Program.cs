using System;
using System.IO.Ports;
using System.Threading;
using System.Windows.Forms;
using System.IO;

using System.Runtime.InteropServices;

namespace LedSteuerung
{
    class Program
    {

 


        public static Random random = new Random() ;
        public static SerialPort myPort;
        public static ConsoleKeyInfo key;
        public static string Nachricht = "";
        public static int Position = 0;
        public static int Blau = 200, Grün = 200, Rot = 10, Modus = 1, Warte = 100, Vor = 100, Hinten = 33, Nfarben6 = 4, Frequenzfilter = 10, PlusMinusRan = 240,CreativeMode = 0;
        public static int[] ints = { Blau, Grün, Rot, Modus, Warte, Vor, Hinten, Nfarben6, Frequenzfilter, PlusMinusRan, CreativeMode };
        public static string[] strings = { "Blau", "Grün", "Rot", "Modus", "Warte", "Vor", "Hinten", "AnzahlderFarben", "Frequenzfilter", "+-Random", "CreativMode" };
        public static bool sendeTaste = false;
        public static bool submodus = true;
        public static string USBanschlussName = "com3";
        public static int USBBaudrate = 9600;
        public static string Taste = "";
        static void Main(string[] args)
        {
            Console.CursorVisible = false;

            UsbAnschlusskontrolle();
            
            Sendewert();
            Console.Write(myPort.ReadExisting());


        }
        static void Optionen()
        {
            Position = 0;
            Taste = "";
            bool Enter = false;
            myPort.Close();
            Console.Clear();
            Schreiben("Baudrate: " + USBBaudrate, "black", "green", 0, 0);
            Schreiben("Portname: " + USBanschlussName, "black", "white", 0, 1);
            Schreiben("Submodus: " + submodus, "black", "white", 0, 2);
            while (Taste != "Escape")
            {
                Thread.Sleep(10);
                key = Console.ReadKey(true);
                Taste = key.Key.ToString();
                if (Enter)
                {
                    switch (Position)
                    {
                        case 0: USBBaudrate = ZahlenString(Taste, USBBaudrate, 99); break;
                        case 1: USBanschlussName = TastenString(Taste, USBanschlussName); break;
                        case 2:
                            if (Taste == "UpArrow" || Taste == "W" || Taste == "DownArrow" || Taste == "S")
                            {
                                if (submodus)
                                    submodus = false;
                                else submodus = true;
                            }
                            break;
                        default: break;
                    }
                }
                else
                {
                    if (Taste == "UpArrow" || Taste == "W")
                    {
                        if (Position != 0) Position--;

                    }
                    if (Taste == "DownArrow" || Taste == "S")
                    {
                        if (Position != 2) Position++;
                    }
                }
                if (Taste == "Enter")
                {

                    if (Enter)
                    {
                        Enter = false;
                    }
                    else
                    {
                        Enter = true;

                    }
                }
                if (Enter == false)
                {
                    switch (Position)
                    {
                        case 0:
                            Schreiben("Baudrate: " + USBBaudrate, "black", "green", 0, 0);
                            Schreiben("Portname: " + USBanschlussName, "black", "white", 0, 1); break;
                        case 1:
                            Schreiben("Baudrate: " + USBBaudrate, "black", "white", 0, 0);
                            Schreiben("Portname: " + USBanschlussName, "black", "green", 0, 1);
                            Schreiben("Submodus: " + submodus, "black", "white", 0, 2); break;
                        case 2:
                            Schreiben("Portname: " + USBanschlussName, "black", "white", 0, 1);
                            Schreiben("Submodus: " + submodus, "black", "green", 0, 2); break;
                    }
                }
                else
                {
                    switch (Position)
                    {
                        case 0: Schreiben("Baudrate: " + USBBaudrate + " ", "black", "cyan", 0, 0); break;
                        case 1: Schreiben("Portname: " + USBanschlussName + " ", "black", "cyan", 0, 1); break;
                        case 2: Schreiben("Submodus: " + submodus + " ", "black", "cyan", 0, 2); break;
                    }
                }
            }
            UsbAnschlusskontrolle();
        }
        static void UsbAnschlusskontrolle()
        {
            try
            {
                myPort = new SerialPort();
                myPort.PortName = USBanschlussName;
                myPort.BaudRate = USBBaudrate;
                myPort.ReadTimeout = 500;
                myPort.Open();
                Schreiben("Arduino erkannt", "black", "green", 0, 0);
                Thread.Sleep(500);
            }
            catch (Exception)
            {
                Schreiben("Arduino nicht angeschlossen", "black", "red", 0, 0);
                Schreiben("Evt anderer Port?", "black", "red", 0, 1);
                Console.ReadKey();
                ab1:
                Console.Clear();
                string[] ports = SerialPort.GetPortNames();
                Console.ForegroundColor = ConsoleColor.Green;
                foreach (string port in ports)
                {
                    Console.WriteLine(port);
                }
                Console.ForegroundColor = ConsoleColor.Cyan;
                Console.WriteLine("Portname?");
                USBanschlussName = Console.ReadLine();
                USBanschlussName = USBanschlussName.ToUpper();
                bool Namevorhanden = false;
                foreach (string port in ports)
                {
                    if (USBanschlussName == port)
                    {
                        Namevorhanden = true;
                    }
                }
                if (Namevorhanden == false)
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.WriteLine("Portname nicht vorhanden");
                    Console.ReadKey();
                    goto ab1;
                }
                try
                {
                    myPort = new SerialPort();
                    myPort.PortName = USBanschlussName.ToUpper();
                    myPort.BaudRate = USBBaudrate;
                    myPort.ReadTimeout = 500;
                    myPort.Open();
                    Console.Clear();
                    Schreiben("Arduino erkannt", "black", "green", 0, 0);
                    Console.ReadKey();
                }
                catch (Exception)
                {
                    Application.Exit();
                }

            }
            Console.Clear();
        }
        static void Programm()
        {
            Console.Clear();
            Console.WriteLine("Programm gestartet");
            while(Console.KeyAvailable == false)
            {
                if (!File.Exists(Application.StartupPath + "\\Test.txt"))
                {
                    Console.WriteLine("Test.txt konnte nicht gefunden werden");
                }
                else
                {
                    string line;
                    StreamReader file = new StreamReader(Application.StartupPath + "\\Test.txt");
                    Schreiben("TXT datei", "black", "green", 0, 10);
                    while ((line = file.ReadLine()) != null)
                    {
                        if(line.IndexOf("t") == 0)
                        {
                            int sleep = 0;
                            line = line.Remove(0, 1);
                            Console.WriteLine(line);
                            sleep = Convert.ToInt32(line);
                            Console.WriteLine("thread wird für " + sleep + "ms angehalten");
                            Thread.Sleep(sleep);
                        }
                        myPort.Write(line);
                        Console.WriteLine(line);
                        Thread.Sleep(1000);
                    }
                    Thread.Sleep(20000);
                    file.Close();
                }
                
                for (int i = 0; i < 50 && !Console.KeyAvailable ; i++)
                {
                    Thread.Sleep(1000);
                    switch (i)
                    {
                        case 0: myPort.Write("4b100"); break;
                        case 1: myPort.Write("4b200"); break;
                        case 2: myPort.Write("1b"); break;
                        default:
                            ints[3] = random.Next(0, 30); myPort.Write(StringaufbauSub(3)); Thread.Sleep(4000);
                            break;
                    }
                   
                }
                
            }
        }
        static void Sendewert()
        {
            while (true)
            {
                Schreiben("Baudrate: " + USBBaudrate, "black", "white", 79, 1);
                Schreiben("Port: " + USBanschlussName, "black", "white", 79, 2);
                Schreiben("Submodus: " + submodus, "black", "white", 79, 3);
                Position = Menü(strings, ref ints, Position);
                if (submodus)
                {
                    myPort.Write(StringaufbauSub(Position));
                }
                else
                {
                    myPort.Write(Stringaufbau(Position));
                }
                Console.SetCursorPosition(45, 0);
                Console.Write("Nachricht gesendet: {0:HH:mm:ss.fff}", DateTime.Now);
                Schreiben("                                    ", "black", "white", 0, 20);
                Schreiben("                                   ", "black", "white", 0, 21);
                Schreiben("                                    ", "black", "white", 0, 22);
                Schreiben("                                    ", "black", "white", 0, 23);
                Schreiben("                                     ", "black", "white", 0, 24);
                Schreiben("                                     ", "black", "white", 0, 25);
                Schreiben("                                     ", "black", "white", 0, 26);
                Schreiben("                                    ", "black", "white", 0, 27);
                Schreiben("                                     ", "black", "white", 0, 28);
            }
        }
        static void Leseusbanschluss()
        {
           string Portnachricht = myPort.ReadExisting();

            if (Portnachricht.Contains("~"))
            {
                Schreiben("Fehler", "black", "red", 0, 12);
              
                myPort.Write(StringaufbauSub(Position));
            }
            else
            {
                Schreiben("       ", "black", "white", 0, 12);
                Nachricht += Portnachricht;
                Console.SetCursorPosition(0, 18);
                Console.Write(Nachricht);
            }
              if(Portnachricht.Contains("Fenster"))
            {
                Programmfenster.Nachrichtzuweisen(Portnachricht);
            } 
            if(Portnachricht.Length ==1)
            {
                
                if (Portnachricht == "p") myPort.Write("100");
                if (Portnachricht == "r") myPort.Write("250");
                if (Portnachricht == "g") myPort.Write("100");
                if (Portnachricht == "b") myPort.Write("100");

            }
        }
        public static int Menü(string[] ArrayString, ref int[] ArrayInt, int Position_)
        {
            Schreiben("Baudrate: " + USBBaudrate, "black", "white", 79, 1);
            Schreiben("Port: " + USBanschlussName, "black", "white", 79, 2);
            Schreiben("Submodus: " + submodus, "black", "white", 79, 3);
            Schreiben("Reset Nachrichten:Q", "black", "white", 100, 1);
            Schreiben("Paramater syn.   :S", "black", "white", 100, 2);
            Schreiben("Programm         :P", "black", "white", 100, 3);
            if (ArrayInt.GetLength(0) != ArrayString.GetLength(0))
            {
                Schreiben("Die übergebene Arrays sind nicht gleich lang", "black", "red", 0, 0);
                return 0;
            }
            int Anzahl = 0, Modus = 0, ZeilenPosition = Position_;
            string Taste = "";
            while (ArrayString.GetLength(0) != Anzahl)
            {
                Schreiben(ArrayString[Anzahl] + ": " + ArrayInt[Anzahl], "black", "white", 0, Anzahl);
                Anzahl++;
            }
            Schreiben(ArrayString[ZeilenPosition] + ": " + ArrayInt[ZeilenPosition], "black", "green", 0, ZeilenPosition);
            while (true)
            {
              Thread.Sleep(10);
                //Lese den Buffer von usb anschluss aus
                if (myPort.BytesToRead != 0)
                {
                    Console.SetCursorPosition(45, 1);
                    Console.Write("Nachricht empfangen {0:HH:mm:ss.fff}", DateTime.Now);
                    Thread.Sleep(10);
                    Leseusbanschluss();
                }
                if (Console.KeyAvailable)
                {
                    key = Console.ReadKey(true);
                    Taste = key.Key.ToString();
                    if (Taste == "Escape")
                    {
                        Optionen();
                    }
                    if (Taste == "Enter")
                    {
                        if (Modus == 0)
                        {
                            Modus = 1;
                        }
                        else Modus = 0;
                    }
                    if (Taste == "RightArrow")
                    {
                        Schreiben(ArrayString[ZeilenPosition] + ": " + ArrayInt[ZeilenPosition] + "  ", "black", "green", 20, ZeilenPosition);
                        return ZeilenPosition;
                    }
                    if(Taste == "S")
                    {
                        Synchronisieren();
                        Anzahl = 0;
                     
                        while (ArrayString.GetLength(0) != Anzahl)
                        {
                            Schreiben(ArrayString[Anzahl] + ": " + ArrayInt[Anzahl]+"  ", "black", "white", 0, Anzahl);
                            Anzahl++;
                        }
                    }
                    if (Taste == "Q")
                    {
                        Nachricht = " ";
                    }
                    if(Taste == "P")
                    {
                        Programm();
                    }
                    if (Taste == "B" || Taste == "G" || Taste == "R" || Taste == "M" || Taste == "W" || Taste == "F" || Taste == "V" || Taste == "H" || Taste == "A" || Taste == "F" || Taste == "P")
                    {
                        sendeTaste = true;
                        Console.ForegroundColor = ConsoleColor.White;
                        Console.SetCursorPosition(0, ZeilenPosition);
                        Console.Write(ArrayString[ZeilenPosition] + ": " + ArrayInt[ZeilenPosition]);
                        switch (Taste)
                        {
                            case "B": ZeilenPosition = 0; break;
                            case "G": ZeilenPosition = 1; break;
                            case "R": ZeilenPosition = 2; break;
                            case "M": ZeilenPosition = 3; break;
                            case "W": ZeilenPosition = 4; break;
                            case "V": ZeilenPosition = 5; break;
                            case "H": ZeilenPosition = 6; break;
                            case "A": ZeilenPosition = 7; break;
                            case "F": ZeilenPosition = 8; break;
                            case "P": ZeilenPosition = 9; break;
                            default: break;
                        }
                        Console.ForegroundColor = ConsoleColor.Green;
                        Console.SetCursorPosition(0, ZeilenPosition);
                        Console.Write(ArrayString[ZeilenPosition] + ": " + ArrayInt[ZeilenPosition]);
                    }
                    if (Modus == 0)
                    {
                        if (Taste == "UpArrow")
                        {
                            ZeilenPosition--;
                            if (ZeilenPosition == -1) ZeilenPosition = ArrayString.GetLength(0) - 1;
                            Console.ForegroundColor = ConsoleColor.Green;
                            Console.SetCursorPosition(0, ZeilenPosition);
                            Console.Write(ArrayString[ZeilenPosition] + ": " + ArrayInt[ZeilenPosition]);
                            Console.ForegroundColor = ConsoleColor.White;
                            if (ZeilenPosition != ArrayString.GetLength(0) - 1)
                            {
                                Console.SetCursorPosition(0, ZeilenPosition + 1);
                                Console.Write(ArrayString[ZeilenPosition + 1] + ": " + ArrayInt[ZeilenPosition + 1]);
                            }
                            else
                            {
                                Console.SetCursorPosition(0, 0);
                                Console.Write(ArrayString[0] + ": " + ArrayInt[0]);
                            }
                        }
                        if ( Taste == "DownArrow")
                        {
                            ZeilenPosition++;
                            if (ZeilenPosition == ArrayString.GetLength(0)) ZeilenPosition = 0;


                            Console.ForegroundColor = ConsoleColor.White;
                            if (ZeilenPosition != 0)
                            {
                                Console.SetCursorPosition(0, ZeilenPosition - 1);
                                Console.Write(ArrayString[ZeilenPosition - 1] + ": " + ArrayInt[ZeilenPosition - 1]);
                            }
                            else
                            {
                                Console.SetCursorPosition(0, ArrayString.GetLength(0) - 1);
                                Console.Write(ArrayString[ArrayString.GetLength(0) - 1] + ": " + ArrayInt[ArrayString.GetLength(0) - 1]);
                            }
                        }
                        if (Taste != "UpArrow" && Taste != "W" && Taste != "S" && Taste != "DownArrow" && Taste != "Enter")
                        {
                            if (sendeTaste == true)
                            {
                                if (Taste == "B" || Taste == "G" || Taste == "R" || Taste == "M" || Taste == "W" || Taste == "F" || Taste == "V" || Taste == "H")
                                {
                                }
                                else
                                {
                                    sendeTaste = false;
                                    ArrayInt[ZeilenPosition] = 0;
                                }
                            }
                            ArrayInt[ZeilenPosition] = ZahlenString(Taste, ArrayInt[ZeilenPosition], ZeilenPosition);
                            Console.SetCursorPosition(0, ZeilenPosition);
                        }
                        Console.SetCursorPosition(0, ZeilenPosition);
                        Console.ForegroundColor = ConsoleColor.Green;
                        Console.Write(ArrayString[ZeilenPosition] + ": " + ArrayInt[ZeilenPosition] + "   ");
                    }
                    if (Modus == 1)
                    {
                        ArrayInt[ZeilenPosition] = ZahlenString(Taste, ArrayInt[ZeilenPosition], ZeilenPosition);
                        Console.ForegroundColor = ConsoleColor.Cyan;
                        Console.SetCursorPosition(0, ZeilenPosition);
                        Console.Write(ArrayString[ZeilenPosition] + ": " + ArrayInt[ZeilenPosition] + " ");
                    }
                    ModusInformationen(ints[3]);
                }
            }
        }
        public static void Synchronisieren()
        {
            myPort.Write("1S");
            while (myPort.BytesToRead == 0)
            {
                Thread.Sleep(1);
            }
            Thread.Sleep(500);
            string Portnachricht = myPort.ReadExisting();
            int anfang = Portnachricht.IndexOf("BLAU");
            Portnachricht = Portnachricht.Remove(0, anfang+4);
            int Gruencut = Portnachricht.IndexOf("G");
            ints[0] = Convert.ToInt32(Portnachricht.Remove(Gruencut, Portnachricht.Length-Gruencut));
            Portnachricht = Portnachricht.Remove(0, Gruencut+1);

            int Rotcut = Portnachricht.IndexOf("R");
            ints[1] = Convert.ToInt32(Portnachricht.Remove(Rotcut, Portnachricht.Length - Rotcut));
            Portnachricht = Portnachricht.Remove(0, Rotcut + 1);

            int Blaucut = Portnachricht.IndexOf("M");
            ints[2] = Convert.ToInt32(Portnachricht.Remove(Blaucut, Portnachricht.Length - Blaucut));
            Portnachricht = Portnachricht.Remove(0, Blaucut + 1);

            int wartecut = Portnachricht.IndexOf("W");
            ints[3] = Convert.ToInt32(Portnachricht.Remove(wartecut, Portnachricht.Length - wartecut));
            Portnachricht = Portnachricht.Remove(0, wartecut + 1);

            int vorcut = Portnachricht.IndexOf("V");
            ints[4] = Convert.ToInt32(Portnachricht.Remove(vorcut, Portnachricht.Length - vorcut));
            Portnachricht = Portnachricht.Remove(0, vorcut + 1);

            int hintercut = Portnachricht.IndexOf("H");
            ints[5] = Convert.ToInt32(Portnachricht.Remove(hintercut, Portnachricht.Length - hintercut));
            Portnachricht = Portnachricht.Remove(0, hintercut + 1);

            int anzahlcut = Portnachricht.IndexOf("A");
            ints[6] = Convert.ToInt32(Portnachricht.Remove(anzahlcut, Portnachricht.Length - anzahlcut));
            Portnachricht = Portnachricht.Remove(0, anzahlcut + 1);

            int filtercut = Portnachricht.IndexOf("F");
            ints[7] = Convert.ToInt32(Portnachricht.Remove(filtercut, Portnachricht.Length - filtercut));
            Portnachricht = Portnachricht.Remove(0, filtercut + 1);
        }
        public static void Farben(string Hintergrundfarbe, string Vordergrundfarbe)
        {
            switch (Hintergrundfarbe)
            {
                case "black": Console.BackgroundColor = ConsoleColor.Black; break;
                case "white": Console.BackgroundColor = ConsoleColor.White; break;
                case "blue": Console.BackgroundColor = ConsoleColor.Blue; break;
                case "red": Console.BackgroundColor = ConsoleColor.Red; break;
                case "yellow": Console.BackgroundColor = ConsoleColor.Yellow; break;
                case "green": Console.BackgroundColor = ConsoleColor.Green; break;
                case "gray": Console.BackgroundColor = ConsoleColor.Gray; break;
                case "magenta": Console.BackgroundColor = ConsoleColor.Magenta; break;
                case "cyan": Console.BackgroundColor = ConsoleColor.Cyan; break;
                case "darkblue": Console.BackgroundColor = ConsoleColor.DarkBlue; break;
                case "darkgreen": Console.BackgroundColor = ConsoleColor.DarkGreen; break;
                case "darkred": Console.BackgroundColor = ConsoleColor.DarkRed; break;
                case "darkgray": Console.BackgroundColor = ConsoleColor.DarkGray; break;
                case "darkcyan": Console.BackgroundColor = ConsoleColor.DarkCyan; break;
                case "darkmagenta": Console.BackgroundColor = ConsoleColor.DarkMagenta; break;
                default: break;
            }
            switch (Vordergrundfarbe)
            {
                case "black": Console.ForegroundColor = ConsoleColor.Black; break;
                case "white": Console.ForegroundColor = ConsoleColor.White; break;
                case "blue": Console.ForegroundColor = ConsoleColor.Blue; break;
                case "red": Console.ForegroundColor = ConsoleColor.Red; break;
                case "yellow": Console.ForegroundColor = ConsoleColor.Yellow; break;
                case "green": Console.ForegroundColor = ConsoleColor.Green; break;
                case "gray": Console.ForegroundColor = ConsoleColor.Gray; break;
                case "magenta": Console.ForegroundColor = ConsoleColor.Magenta; break;
                case "cyan": Console.ForegroundColor = ConsoleColor.Cyan; break;
                case "darkblue": Console.ForegroundColor = ConsoleColor.DarkBlue; break;
                case "darkgreen": Console.ForegroundColor = ConsoleColor.DarkGreen; break;
                case "darkred": Console.ForegroundColor = ConsoleColor.DarkRed; break;
                case "darkgray": Console.ForegroundColor = ConsoleColor.DarkGray; break;
                case "darkcyan": Console.ForegroundColor = ConsoleColor.DarkCyan; break;
                case "darkmagenta": Console.ForegroundColor = ConsoleColor.DarkMagenta; break;
                default: break;
            }
        }
        public static void Schreiben(string text, string Hintergrundfarbe, string Vordergrundfarbe, int x, int y)
        {
            Console.SetCursorPosition(x, y);
            Farben(Hintergrundfarbe, Vordergrundfarbe);
            Console.Write(text);
            Console.BackgroundColor = ConsoleColor.Black;
        }
        public static string Stringaufbau(int Position_)
        {
            string rückgabe = "";
            switch (Position_)
            {
                case 0: rückgabe = "b" + ints[0]; break;
                case 1: rückgabe = "g" + ints[1]; break;
                case 2: rückgabe = "r" + ints[2]; break;
                case 3: rückgabe = "m" + ints[3]; break;
                case 4: rückgabe = "w" + ints[4]; break;
                case 5: rückgabe = "v" + ints[5]; break;
                case 6: rückgabe = "h" + ints[6]; break;
                case 7: rückgabe = "n" + ints[7]; break;
                case 8: rückgabe = "f" + ints[8]; break;
                default: break;
            }
            return rückgabe;
        }
        public static string StringaufbauSub(int Position_)
        {
            string a = Convert.ToString(ints[Position_]);
            int Länge = a.Length + 1;
            string rückgabe = "";
            switch (Position_)
            {

                case 0: rückgabe = "b" + ints[0]; break;
                case 1: rückgabe = "g" + ints[1]; break;
                case 2: rückgabe = "r" + ints[2]; break;
                case 3: rückgabe = "m" + ints[3]; break;
                case 4: rückgabe = "w" + ints[4]; break;
                case 5: rückgabe = "v" + ints[5]; break;
                case 6: rückgabe = "h" + ints[6]; break;
                case 7: rückgabe = "n" + ints[7]; break;
                case 8: rückgabe = "f" + ints[8]; break;
                case 9: rückgabe = "p" + ints[9]; break;
                case 10: rückgabe = "c" + ints[10]; break;
                default: break;

            }
            return Länge + rückgabe;
        }
        static int ZahlenString(string Taste, int Zahl, int zeile)
        {
            int Wert = 0;
            string Zahlenstring = Convert.ToString(Zahl);
            switch (Taste)
            {
                case "NumPad1":
                case "D1": Zahlenstring = Zahlenstring.Insert(Zahlenstring.Length, "1"); break;
                case "NumPad2":
                case "D2": Zahlenstring = Zahlenstring.Insert(Zahlenstring.Length, "2"); break;
                case "NumPad3":
                case "D3": Zahlenstring = Zahlenstring.Insert(Zahlenstring.Length, "3"); break;
                case "NumPad4":
                case "D4": Zahlenstring = Zahlenstring.Insert(Zahlenstring.Length, "4"); break;
                case "NumPad5":
                case "D5": Zahlenstring = Zahlenstring.Insert(Zahlenstring.Length, "5"); break;
                case "NumPad6":
                case "D6": Zahlenstring = Zahlenstring.Insert(Zahlenstring.Length, "6"); break;
                case "NumPad7":
                case "D7": Zahlenstring = Zahlenstring.Insert(Zahlenstring.Length, "7"); break;
                case "NumPad8":
                case "D8": Zahlenstring = Zahlenstring.Insert(Zahlenstring.Length, "8"); break;
                case "NumPad9":
                case "D9": Zahlenstring = Zahlenstring.Insert(Zahlenstring.Length, "9"); break;
                case "NumPad0":
                case "D0": Zahlenstring = Zahlenstring.Insert(Zahlenstring.Length, "0"); break;
                case "Backspace":
                    if (Zahlenstring != "")
                    {
                        int num1 = Zahlenstring.Length;
                        Zahlenstring = Zahlenstring.Remove(num1 - 1, 1);
                    }
                    break;
                default: break;
            }
            if (Zahlenstring == "")
            {
                Wert = 0;
            }
            else
            {
                try
                {
                    Wert = Convert.ToInt32(Zahlenstring);
                }
                catch
                {
                    Wert = 255;
                }
            }
            if (Taste == "UpArrow" || Taste == "W")
                Wert++;
            if (Taste == "DownArrow" || Taste == "S")
                Wert--;
            switch (zeile)
            {
                case 0:
                case 1:
                case 2: if (Wert > 254) Wert = 254; break;
                case 7: if (Wert > 200) Wert = 199; break;

                default: break;
            }
            if (Wert <= 0)
                Wert = 0;
            return Wert;
        }
        static string TastenString(string Taste, string Text)
        {
            if (Taste == "Backspace")
            {
                int num1 = Text.Length;
                Text = Text.Remove(num1 - 1, 1);
            }
            else if (Taste.Length == 2)
            {
                Taste = Taste.Remove(0, 1);
                Text = Text + Taste;
            }
            else if (Taste != "Enter")
            {
                Text = Text + Taste;
            }
            return Text;
        }
        static void ModusInformationen(int Modus)
        {
            Schreiben("                                                                           ", "black", "white", 45, 10);
            Schreiben("                                                                           ", "black", "white", 61, 11);
            Schreiben("Abhängigkeiten:", "black", "white", 45, 11);
            switch (Modus)
            {
                case 0:
                    Schreiben("Alle Leds nehmen gleichzeitig die gleiche Farbe an", "black", "white", 45, 10);      break;       
                case 1:
                    Schreiben("Alle Leds nehmen verzögert die gleiche Farbe an", "black", "white", 45, 10);
                    Schreiben("Warte,Rot,Blau,Grün", "black", "cyan", 61, 11); break;
                case 2:
                    Schreiben("Alle leds werden nacheinander an/ausgeschaltet", "black", "white", 45, 10);
                    Schreiben("Warte,Rot,Blau,Grün", "black", "cyan", 61, 11); break;
                 case 3:
                    Schreiben("Alle Leds werden sofort an/aus geschalten", "black", "white", 45, 10);
                    Schreiben("Warte,Rot,Blau,Grün", "black", "cyan", 61, 11); break;
                case 4:
                    Schreiben("Alle Leds werden abwechselnd heller/dunkler", "black", "white", 45, 10);
                    Schreiben("Warte,Rot,Blau,Grün", "black", "cyan", 61, 11); break;
                case 5:
                    Schreiben("Erste Led wird gefärbt und wird weiter gereicht ", "black", "white", 45, 10);
                    Schreiben("Warte,Rot,Blau,Grün,Vor,Hinten                  ", "black", "cyan", 61, 11); break;
                case 7:
                    Schreiben("Es Werden zufällig generierte Leds vor/zurück geschoben", "black", "white", 45, 10);
                    Schreiben("Abhängigkeiten:", "black", "white", 45, 11);
                    Schreiben("Warte,Randomwert", "black", "cyan", 61, 11); break;
                case 8:
                    Schreiben("Led wird nach Basstärke gefärbt(Weiß)", "black", "white", 45, 10);
                    Schreiben("Warte,Bass", "black", "cyan", 61, 11); break;
                case 9:
                    Schreiben("Led wird nach Basstärke gefärbt(Bunt)", "black", "white", 45, 10);
                    Schreiben("Warte,Bass,Rot,Blau,Grün", "black", "cyan", 61, 11); break;
                case 10:
                    Schreiben("Led wechselt die Farbe in rot/blau", "black", "white", 45, 10);
                    Schreiben("Warte", "black", "cyan", 61, 11); break;
                case 11:
                    Schreiben("Zufällige farbige Streifen", "black", "white", 45, 10);
                    Schreiben("Abhängigkeiten:", "black", "white", 45, 11);
                    Schreiben("Vor,Hinter, Warte ", "black", "cyan", 61, 11); break;
                case 12:
                    Schreiben("Farbiger Bass Equalizer                            ", "black", "white", 45, 10);
                    Schreiben("Rot,Blau,Grün,Vor,Bass                         ", "black", "cyan", 61, 11); break;
                case 13:
                    Schreiben("Bass Equalizer von grün nach rot                  ", "black", "white", 45, 10);
                    Schreiben("Bass                         ", "black", "cyan", 61, 11); break;
                case 14:
                    Schreiben("Streifen die dunkler/heller werden                ", "black", "white", 45, 10);
                    Schreiben("Warte,Rot,Blau,Grün,Vor,Hinter                      ", "black", "cyan", 61, 11); break;
                case 15:
                    Schreiben("Regenbogen Streifen             ", "black", "white", 45, 10);
                    Schreiben("Abhängigkeiten:", "black", "white", 45, 11);
                    Schreiben("Warte                           ", "black", "cyan", 61, 11); break;
                 case 16:
                    Schreiben("Zufällige weiche Streifen(Farbig)", "black", "white", 45, 10);
                    Schreiben("Warte,Randomwert,Blau,Rot,Grün", "black", "cyan", 61, 11); break;
                case 17:
                    Schreiben("Led wird Blockmässig aus/an geschalten", "black", "white", 45, 10);
                    Schreiben("Warte,Farbanzahl,Rot,Blau,Grün", "black", "cyan", 61, 11); break;
                case 18:
                    Schreiben("Streifen die Abgedunkelt werden                               ", "black", "white", 45, 10);
                    Schreiben("Warte,Rot,Blau,Grün,Randomwert,Farbanzahl", "black", "cyan", 61, 11); break;
                 case 19:
                    Schreiben("Streifen die Abgedunkelt werden und durch Bass entstehen                 ", "black", "white", 45, 10);
                    Schreiben("Warte,Rot,Blau,Grün,Bass,Farbanzahl ", "black", "cyan", 61, 11); break;
                case 20:
                    Schreiben("Einzelne Leds werden abgedunkelt und erscheinen            ", "black", "white", 45, 10);
                    Schreiben("Warte,Rot,Blau,Grün                           ", "black", "cyan", 61, 11); break;
                case 21:
                    Schreiben("Es entsehen Farbige/Schwarze Streifen           ", "black", "white", 45, 10);
                    Schreiben("Warte,Rot,Blau,Grün, Vor,Hinten                           ", "black", "cyan", 61, 11); break;
                case 22:
                    Schreiben("Bassabhängige Weiße Streifen           ", "black", "white", 45, 10);
                    Schreiben("Bass,Warte                         ", "black", "cyan", 61, 11); break;
                case 23:
                    Schreiben("Bassabhängige Weiße Streifen die abnehmen      ", "black", "white", 45, 10);
                    Schreiben("Bass,Warte  ", "black", "cyan", 61, 11); break;
                case 24:
                    Schreiben("Bassabhängige Farbige Streifen  ", "black", "white", 45, 10);
                    Schreiben("Bass,Warte,Rot,Blau,Grün  ", "black", "cyan", 61, 11); break;
                case 25:
                    Schreiben("Bassabhängige Farbige Streifen die abnehmen ", "black", "white", 45, 10);
                    Schreiben("Abhängigkeiten:", "black", "white", 45, 11);
                    Schreiben("Bass,Warte,Rot,Blau,Grün          ", "black", "cyan", 61, 11); break;
                case 26:
                    Schreiben("Einzelne Leds werden abgedunkelt und erscheinen durch Bass           ", "black", "white", 45, 10);
                    Schreiben("Rot,Blau,Grün,Bass                           ", "black", "cyan", 61, 11); break;
                case 27:
                    Schreiben("Bassabhängige/bewegliche Spawner          ", "black", "white", 45, 10);
                    Schreiben("Abhängigkeiten:", "black", "white", 45, 11);
                    Schreiben("Warte,Rot,Blau,Grün,Bass,Vor,Farbanzahl                           ", "black", "cyan", 61, 11); break;
                case 28:
                    Schreiben("BassabhängigeSpawner          ", "black", "white", 45, 10);
                    Schreiben("Warte,Rot,Blau,Grün,Bass,Farbanzahl                           ", "black", "cyan", 61, 11); break;
                case 29:
                    Schreiben("Bassabhängige/bewegliche Leds         ", "black", "white", 45, 10);
                    Schreiben("Warte,Rot,Blau,Grün,Bass,Farbanzahl                           ", "black", "cyan", 61, 11); break;
                case 30:
                    Schreiben("Bassabhängige/bewegliche Spawnstreifen(Farblimit = 2500 ", "black", "white", 45, 10);
                    Schreiben("Warte,Rot,Blau,Grün,Bass,Vor,Farbanzahl", "black", "cyan", 61, 11); break;
                case 31:
                    Schreiben("Bassabhängige/bewegliche Spawnstreifen(Farblimit = 250 ", "black", "white", 45, 10);
                    Schreiben("Warte,Rot,Blau,Grün,Bass,Vor,Farbanzahl", "black", "cyan", 61, 11); break;
                case 32:
                    Schreiben("BassabhängigeSpawner       ", "black", "white", 45, 10);
                    Schreiben("Warte,Rot,Blau,Grün,Bass,Vor,Farbanzahl", "black", "cyan", 61, 11); break;
                case 33:
                    Schreiben("Bass abhängig Raketenstyle      ", "black", "white", 45, 10);
                    Schreiben("Warte,Rot,Blau,Grün,Farbanzahl,Bass", "black", "cyan", 61, 11); break;
                case 34:
                    Schreiben("Bassabhängige leds werden gespawnt und werden verlangsamt  ", "black", "white", 45, 10);
                    Schreiben("Warte,Rot,Blau,Grün,Farbanzahl, Bass", "black", "cyan", 61, 11); break;
                case 35:
                    Schreiben("Led wird Blockmässig aus/an geschalten", "black", "white", 45, 10);
                    Schreiben("Warte,Farbanzahl,Rot,Blau,Grün,Bass", "black", "cyan", 61, 11); break;
                case 40:
                    Schreiben("Raketenstyle      ", "black", "white", 45, 10);
                    Schreiben("Warte,Rot,Blau,Grün,Farbanzahl", "black", "cyan", 61, 11); break;
                case 100:
                    Schreiben("Led stoppen", "black", "white", 45, 10);break;
                case 101:
                    Schreiben("Led abdunkeln", "black", "white", 45, 10);break;
                case 102:
                    Schreiben("Leds vor verschieben", "black", "white", 45, 10);break;
                case 103:
                    Schreiben("Leds hinter verschieben", "black", "white", 45, 10); break;
                case 200:
                    Schreiben("Listet das gesamte Array(Einzelwerte) auf", "black", "white", 45, 10); break;
                case 201:
                    Schreiben("löscht das Array                                      ", "black", "white", 45, 10); break;
                case 202:
                    Schreiben("Listet die zwischenwerte auf", "black", "white", 45, 10); break;
                case 203:
                    Schreiben("Leds Werte werden ins Array eingespeichert", "black", "white", 45, 10); break;
                default: break;
            }
        }
        static void CreativInformation(int Modus)
        {
            Schreiben("                                                                           ", "black", "white", 45, 10);
            Schreiben("                                                                           ", "black", "white", 61, 11);
            switch (Modus)
            {
                case 0: Schreiben("Leds können per USB einzeln gefärbt werden", "black", "white", 45, 10); break;
                case 1: Schreiben("Debugmodus aktivieren/deaktivieren", "black", "white", 45, 10); break;
                case 2: Schreiben("Startcounter neustarten", "black", "white", 45, 10); break;
            }
        }
    }
}

