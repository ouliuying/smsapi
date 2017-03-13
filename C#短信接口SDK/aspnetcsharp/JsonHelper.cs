using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace aspnetcsharp
{
    public class JsonHelper
    {
        public static string MakeNameValue<T>(string name, T value)
        {
            return String.Format("\"{0}\":\"{1}\"", name, value);
        }
        public static string MakeNameArray(string name, List<string> arr)
        {
            string retstr = String.Join(",", arr.ToArray());
            retstr = "[" + retstr + "]";
            return String.Format("\"{0}\":{1}", name, retstr);
        }
        public static string MakeNameArray(string name,string  data)
        {
            return String.Format("\"{0}\":{1}", name, data);
        }
        public static string MakeNameArray<T>(string name, List<T> arr)
        {
            string retstr = String.Join(",", arr.ToArray());
            retstr = "[" + retstr + "]";
            return String.Format("\"{0}\":{1}", name, retstr);
        }
    }
}