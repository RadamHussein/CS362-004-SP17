/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;




/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, 0);

       // Expected Pass
       System.out.print("THESE SHOULD ALL PASS\n");
       System.out.println(urlVal.isValid("http://www.google.com"));
       System.out.println(urlVal.isValid("http://www.google.com/"));
       System.out.println(urlVal.isValid("http://www.google.com?")); //FAILED
       System.out.println(urlVal.isValid("http://www.google.com:88"));
       System.out.println(urlVal.isValid("http://www.google.com?key=val")); //FAILED
       System.out.println(urlVal.isValid("http://www.google.com?key=val&newkey=newval")); //FAILED
       System.out.println(urlVal.isValid("https://www.google.com"));
       System.out.println(urlVal.isValid("https://www.google.com/"));
       System.out.println(urlVal.isValid("https://www.google.com?")); //FAILED
       System.out.println(urlVal.isValid("https://www.google.com:88"));
       System.out.println(urlVal.isValid("https://www.google.com?key=val"));
       System.out.println(urlVal.isValid("https://www.google.com?key=val&newkey=newval")); //FAILED
       System.out.println(urlVal.isValid("0.0.0.0")); //FAILED
       System.out.println(urlVal.isValid("ftp://username@hostname/")); //FAILED

       // Expected Failures
       System.out.print("THESE SHOULD ALL FAIL\n");
       System.out.println(urlVal.isValid(""));
       System.out.println(urlVal.isValid("--http://www.google.com"));
       System.out.println(urlVal.isValid("https://///www.google.com"));
       System.out.println(urlVal.isValid("https://www.google.com/../"));
       System.out.println(urlVal.isValid("https://www.google.com//test"));
       System.out.println(urlVal.isValid("https://///www.google.com"));
       System.out.println(urlVal.isValid("https://///www.google.com"));
       System.out.println(urlVal.isValid("https://///www.google.com"));
       System.out.println(urlVal.isValid("https://www.google.com:-1"));
       System.out.println(urlVal.isValid("https://www.google.com:88z"));

       System.out.println(urlVal.isValid("https://www.google.com:8080")); //FAILED
       

   }

   public void testIsValidPartitions()
   {
       UrlValidator urlVal = new UrlValidator(null, null, 0);
       String test;

       for(int i = 0; i < testUrlScheme.length; i++)
       {
           for (int j = 0; j < testUrlAuthority.length; j++) {

               for (int k = 0; k < testUrlPort.length; k++) {

                   for (int l = 0; l < testPath.length; l++) {

                       for (int m = 0; m < testUrlQuery.length; m++) {

                           test = (testUrlScheme[i].item + testUrlAuthority[j].item + testUrlPort[k].item + testPath[l].item + testUrlQuery[m].item);
                           System.out.println(test + " : " + urlVal.isValid(test));
                       }
                   }
               }
           }
       }
   }

    // irocha: adding Apache-style result pairs //13
   ResultPair[] testUrlScheme = {
           // Expected Passes
           new ResultPair("", true),
           new ResultPair("http://", true),
           new ResultPair("https://", true),
           new ResultPair("ftp://", true),
           new ResultPair("h3t://", true),

           // Expected Failures
           new ResultPair("://", false),
           new ResultPair("http:/", false),
           new ResultPair("http:///", false),
           new ResultPair("3ht://", false),
           new ResultPair("123http:/", false),
           new ResultPair("--http://", false),
           new ResultPair("http:", false),
           new ResultPair("http/", false),
   };

    ResultPair[] testUrlAuthority = { //30
            // Expected Passes
            new ResultPair("google.com", true),
            new ResultPair("www.google.com", true),
            new ResultPair("oregonstate.edu", true),
            new ResultPair("www.oregonstate.edu", true),
            new ResultPair("whitehouse.gov", true),
            new ResultPair("www.whitehouse.gov", true),
            new ResultPair("speedtest.net", true),
            new ResultPair("www.speedtest.net", true),

            new ResultPair("go.com", true),
            new ResultPair("go.co", true),
            new ResultPair("go.ca", true),

            new ResultPair("0.0.0.0", true),
            new ResultPair("255.255.255.255", true),
            new ResultPair("255.com", true),

            new ResultPair("user@something.com", true),
            new ResultPair("user@something.edu", true),
            new ResultPair("user@something.gov", true),
            new ResultPair("user@something.net", true),

            // Expected Failures
            new ResultPair("256.256.256.256", false),
            new ResultPair("256.0.256.1", false),
            new ResultPair("google", false),
            new ResultPair("5.4.3.2.1", false),
            new ResultPair("255", false),
            new ResultPair("go.x", false),
            new ResultPair("go.x1x", false),
            new ResultPair("go.1xx", false),
            new ResultPair("com.", false),
            new ResultPair(".com", false),
            new ResultPair("com", false),
            new ResultPair("", false)
    };

    ResultPair[] testUrlPort = { //8
            // Expected Passes
            new ResultPair("", true),
            new ResultPair(":0", true),
            new ResultPair(":80", true),
            new ResultPair(":8080", true),
            new ResultPair(":65535", true),

            // Expected Failures
            new ResultPair(":-1", false),
            new ResultPair(":23m", false),
            new ResultPair(":XYZ", false),
    };

    ResultPair[] testPath = { //12
            // Expected Passes
            new ResultPair("", true),
            new ResultPair("/test1", true),
            new ResultPair("/t888", true),
            new ResultPair("/$88", true),
            new ResultPair("/dir1/", true),
            new ResultPair("/dir1/file", true),

            // Expected Failures
            new ResultPair("/.", false),
            new ResultPair("./", false),
            new ResultPair("/..", false),
            new ResultPair("/../", false),
            new ResultPair("/..//file", false),
            new ResultPair("/dir1//file", false)
    };


    ResultPair[] testUrlQuery = { //3
            // Expected Passes
            new ResultPair("", true),
            new ResultPair("?key=value", true),
            new ResultPair("?key=value&otherykey=othervalue", true)
    };
}
