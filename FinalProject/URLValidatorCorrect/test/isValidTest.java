import junit.framework.TestCase;

public class isValidTest extends TestCase{
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
	}
	
	public static void main(){
		isValidTest xyz = new isValidTest();
		xyz.testSomeStrings();
	}
}
