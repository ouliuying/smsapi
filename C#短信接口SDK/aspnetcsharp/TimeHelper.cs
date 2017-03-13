using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace aspnetcsharp
{
    public class TimeHelper
    {
        public static string GetUnixTimestampFromLocalTime(DateTime? dt=null)
        {
            if(dt==null)
            {
                dt=DateTime.Now;
            }
            DateTime basetime= new DateTime(1970, 1, 1, 0, 0, 0, 0);
            return Math.Floor((dt.Value.ToUniversalTime()-basetime).TotalSeconds).ToString();
        }
        public static DateTime GetDateTimeFromTimestamp(string timestamp)
        {
            DateTime origin = new DateTime(1970, 1, 1, 0, 0, 0, 0);
            origin = origin.AddSeconds(Convert.ToDouble(timestamp));
            return origin.ToLocalTime();
        }
    }
}