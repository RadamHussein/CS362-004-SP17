import junit.framework.TestCase;

public class isValidTestProg extends TestCase{
	UrlValidator lmn = new UrlValidator();
	
	public void testSomeStrings(){
		assertTrue(lmn.isValid("http://www.google.com"));
		assertTrue(lmn.isValid("http://www.wikipedia.com"));
		assertFalse(lmn.isValid("localhost:8888"));
		assertTrue(lmn.isValid("http://www.whitehouse.gov"));
		assertTrue(lmn.isValid("http://oregonstate.edu"));
		assertFalse(lmn.isValid("http://www.bigcats.wild"));
		assertFalse(lmn.isValid("HTTP://WWW.GOOGLE.COM"));
		assertTrue(lmn.isValid("http://WWW.amazon.com"));
		assertFalse(lmn.isValid("HTTP://www.buildit.com"));
		assertTrue(lmn.isValid("https://bankofeverything.com"));
		assertTrue(lmn.isValid("http://bigpizza.com/toppings=sausage"));
		assertFalse(lmn.isValid("ftp://username@hostname/"));
		assertFalse(lmn.isValid("telnet://melvyl.ucop.edu/"));
		assertTrue(lmn.isValid("http://www.httpwatch.com/features.htm#filter"));
		assertTrue(lmn.isValid("http://example.com:80/"));
	}
	
	public int getTrueOrFalseOption(){
		int x = (int)(Math.random() * 2);
		//System.out.println(x);
		return x;
	}
	
	public String getScheme(int selectArr){
		int schemeIndex;
		//get either a valid or invalid scheme
		if (selectArr == 0){
			schemeIndex = (int)(Math.random() * validSchemes.length);
			return validSchemes[schemeIndex];
		}
		else{
			schemeIndex = (int)(Math.random() * invalidSchemes.length);
			return invalidSchemes[schemeIndex];
		}
	}
	
	public String getAuthority(int selectArr){
		int authorityIndex;
		//get either a valid or invalid scheme
		if (selectArr == 0){
			authorityIndex = (int)(Math.random() * validAuthority.length);
			return validAuthority[authorityIndex];
		}
		else{
			authorityIndex = (int)(Math.random() * invalidAuthority.length);
			return invalidAuthority[authorityIndex];
		}
	}
	
	public String getPort(int selectArr){
		int portIndex;
		//get either a valid or invalid scheme
		if (selectArr == 0){
			portIndex = (int)(Math.random() * validPort.length);
			return validPort[portIndex];
		}
		else{
			portIndex = (int)(Math.random() * invalidPort.length);
			return invalidPort[portIndex];
		}
	}
	
	public String getPath(int selectArr){
		int pathIndex;
		//get either a valid or invalid scheme
		if (selectArr == 0){
			pathIndex = (int)(Math.random() * validPath.length);
			return validPath[pathIndex];
		}
		else{
			pathIndex = (int)(Math.random() * invalidPath.length);
			return invalidPath[pathIndex];
		}
	}
	
	public static void main(String[] args){
		isValidTestProg xyz = new isValidTestProg();
		UrlValidator validator = new UrlValidator();
		int count = 0;
		int val;
		String scheme;
		String authority;
		String port;
		String path;
		String URL;
		boolean expectedResult = true;
		boolean actualResult;
		
		while (count < 11){
			expectedResult = true;
		
			//xyz.testSomeStrings();
			val = xyz.getTrueOrFalseOption();
			
			//if 1, choosing invalid option resulting in invalid URL
			if (val == 1){
				expectedResult = false;
			}
			
			//get a scheme
			scheme = xyz.getScheme(val);
			
			val = xyz.getTrueOrFalseOption();
			
			if (val == 1){
				expectedResult = false;
			}
			
			//get authority
			authority = xyz.getAuthority(val);
			
			val = xyz.getTrueOrFalseOption();
			
			if (val == 1){
				expectedResult = false;
			}
			
			//get port
			port = xyz.getPort(val);
			
			val = xyz.getTrueOrFalseOption();
			
			if (val == 1){
				expectedResult = false;
			}
			
			//get path
			path = xyz.getPath(val);
			
			URL = scheme + authority + port + path;
			
			if (expectedResult == true){
				System.out.println("URL: " + URL);
				System.out.println("Expected: true");
				actualResult = validator.isValid(URL);
				System.out.println("Result: " + actualResult);
				//assertTrue(actualResult);
			}
			else{
				System.out.println("URL: " + URL);
				System.out.println("Expected: false");
				actualResult = validator.isValid(URL);
				System.out.println("Result: " + actualResult);
				//assertFalse(actualResult);
			}
			count++;
		}
	}
	
	String[] validSchemes = {"http://", "https://", "h3t://", ""};
	String[] invalidSchemes = {"http", "http:/", "http//", "https", "://", "3ht://"};
	String[] validAuthority = {"www.google.com", "uk.com", "go.br", "0.0.0.0", "255.255.255.255", "350.com", "gro.aau"};
	String[] invalidAuthority = {"256.256.256.256", "1.2.3.4.5", "1.2.3.4.", "1.2.3", ".1.2.3.4", "go.a", "go.a1a", "go.1aa", "com.", ".com", ""};
	String[] validPort = {":80", ":45245", ":65745", ":32123", ":8088", ":0", ""};
	String[] invalidPort = {":-80", ":2b34", ":800088", "80", "65745"};
	String[] validPath = {"/test", "/12test", "/$test", "/t3st/", "", "/t3st/test", "/t3st/test/"};
	String[] invalidPath = {"/..", "/../", "/test//t3st", "/t3st//test/", "/test...//t3st"};
	String[] validPathOptions = {"/test1", "/test123", "/$123", "/t3st/", "", "/t3st/test2", "/t123/test", "/$123/test", "/t3st//test"};
	String[] invalidPathOption = {"/../", "/..", "/#", "/.../test", "/...//test", "/#/test/"};
	
	
}
