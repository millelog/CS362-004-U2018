

import java.security.SecureRandom;
import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;
import java.util.regex.Pattern;

import junit.framework.TestCase;
import nl.flotsam.xeger.Xeger;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   


	static SecureRandom rnd = new SecureRandom();
	
	String randomString( int len, int alphaNumFlag ){
		String alphabet;
		if(alphaNumFlag>0) {alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";}
		else {alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+_-=\'\"\\!@$%^&*,;:/";}
	   
		StringBuilder sb = new StringBuilder( len );
	   for( int i = 0; i < len; i++ ) 
	      sb.append( alphabet.charAt( rnd.nextInt(alphabet.length()) ) );
	   return sb.toString();
	}


   
   public void testIsValid()
   {
	 //Regular Expressions were sourced from https://commons.apache.org/proper/commons-validator/apidocs/src-html/org/apache/commons/validator/routines/UrlValidator.html
	   //All information to create these regular expressions however is freely available according to the references to url protocols on the apache website

	   String URL_REGEX =
			   "^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?";
	   Pattern URL_PATTERN = Pattern.compile(URL_REGEX);
	   
	   String PATH_REGEX = "^(/[-\\w:@&?=+,.!/~*'%$_;\\(\\)]*)?$";
	   Pattern PATH_PATTERN = Pattern.compile(PATH_REGEX);
	   
	   String QUERY_REGEX = "^(\\S*)$";
	   Pattern QUERY_PATTERN = Pattern.compile(QUERY_REGEX);
	   	   
	   String [] schemes = {"http", "ftp", "https"};
	   String [] domains = {"www.google.com", "www.youtube.com", "www.facebook.com", "www.baidu.com"
			   , "www.wikipedia.org", "www.reddit.com", "www.yahoo.com", "www.qq.com", "www.taobao.com"
			   , "www.amazon.com", "www.tmall.com", "www.twitter.com", "www.sohu.com", "www.instagram.com"
			   , "www.vk.com", "www.live.com", "www.jd.com", "sina.com.cn", "weibo.com", "yandex.ru"
			   , "google.co.jp", "google.ru", "google.com.br", "netflix.com", "google.de"
			   , "google.com.hk", "pornhub.com", "twitch.tv", "google.fr", "linkedin.com", "yahoo.co.jp"
			   , "t.co", "csdn.net", "microsoft.com", "bing.com", "office.com", "ebay.com", "alipay.com"
			   , "xvideos.com", "google.it", "google.ca", "mail.ru", "google.es"
			   , "msn.com"};
	   String URL, path, query, user, pass, i1, i2, i3, i4, port;
	   
	   for(int i=0; i<1000; i++) {
		   URL="";
		   do {			   
			   String scheme = schemes[ThreadLocalRandom.current().nextInt(0, schemes.length)];
			   String domain = domains[ThreadLocalRandom.current().nextInt(0, domains.length)];

			   
//			   if(scheme=="ftp") {
//				   user = randomString(ThreadLocalRandom.current().nextInt(1, 20), 1);
//				   pass = randomString(ThreadLocalRandom.current().nextInt(1, 20), 1);
//				   port = Integer.toString(ThreadLocalRandom.current().nextInt(0, 999));
//				   
//				   URL = scheme+"://"+user+":"+pass+"@"+domain+":"+port;
//			   }
//			   else {
				   do {
					   path = randomString(ThreadLocalRandom.current().nextInt(1, 50 + 1), 0);
				   }while(!PATH_PATTERN.matcher(path).matches());
				   
				   do {
					   query = randomString(ThreadLocalRandom.current().nextInt(0, 50 + 1), 0);
				   }while(!QUERY_PATTERN.matcher(query).matches());
				   
				   
				   URL = scheme+"://"+domain+path+"?"+query;
//			   }
		   	}while(!URL_PATTERN.matcher(URL).matches());
		   
		   UrlValidator val = new UrlValidator();
		   System.out.println(URL);
		   assert(val.isValid(URL));
	   }
	   
	   
   }
   


}
