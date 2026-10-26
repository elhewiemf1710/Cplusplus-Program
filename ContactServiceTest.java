package com.contactservice.model;
import static org.junit.jupiter.api.Assertions.*;
import java.util.HashMap;
import java.util.Map;
import org.junit.jupiter.api.Nested;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class ContactServiceTest {	
	private final Map<String, Contact> contacts = new HashMap<>();
	private ContactService contactService;
	String validId = "1234567";				// Initial Test Data Input for contactId	
	@BeforeEach
	// Setting system to initial input data through class constructor Contact ()
	/**===================================================================
	 				SETUP TEST DATA INPUT BEFORE EACH TEST
	*===================================================================
	 */
    void setUp() {
		
		contactService = new ContactService();
        Contact initialContact = new Contact(validId, "Smith", "Alfred", "9733331444", "2314 main stre");
        contactService.addContact(initialContact); 
    }
        
	@Nested
	class NestedTests{
		@Test
	    @DisplayName("Check that method addContact(contact) adds a valid unique contact")
		/*===================================================================
		 [1] Test adding valid contact collection
		 *===================================================================
		 */
	    void testAddContactMethodSuccess() {			
	       Contact initialContact = new Contact(validId, "Smith", "Alfred", "9733331444", "2314 main stre");      
	       assertDoesNotThrow(() -> contactService.addContact(initialContact),		// call addContact() method
	                "Valid contact should be added without throwing exceptions");
	    }
	
	    @Test
	    @DisplayName("Check NULL contact for exception")
	    /*===================================================================
		 [2]  Test adding null contact collection
		 *===================================================================
		 */
	    void testAddContactThrowsExceptionForNullContact() {
	        Exception exception = assertThrows(IllegalArgumentException.class, () -> {
	            contactService.addContact(null);});
	        assertEquals("contactId invalid", exception.getMessage(), 
	                "Exception message should match null validation failure");
	    }
	    @Test
	    @DisplayName("Should throw Exception when contactId already exists")
	    /*===================================================================
		 [3] Test adding duplicate record collection
		 *===================================================================
		 */
	    void testAddContactThrowsExceptionForDuplicateId() {
	    	Contact initialContact = new Contact(validId, "Smith", "Alfred", "9733331444", "2314 main stre");
	        Contact duplicateContact = new Contact(validId, "David", "Holds", "3013331444", "987 River stre");
	
	        // Add the first contact to populate the memory collection
	        contactService.addContact(initialContact);
	
	        // Attempting to add a contact with the same ID should fail
	        Exception exception = assertThrows(IllegalArgumentException.class, () -> {
	            contactService.addContact(duplicateContact);					// call addContact() method
	        });
	
	        assertEquals("contactId already exists", exception.getMessage(), 
	                "Exception message should match duplicate ID failure");
	    }
	    @Test
	    @DisplayName("Should successfully delete contact when contactId exists")
	   /*===================================================================
		 [4] Test deleting contact record by method: deleteContact(String contactId)
		 *===================================================================  
	    */
	    void shouldRemoveContactWhenIdExists() {
	    	
	    	// Add a dummy collection
	        String contactId = "7654321";
	        contacts.put(contactId,  new Contact("7654321", "Sully", "Holds", "3013331444", "987 River stre"));
	
	        // Delete the dummy collection
	        contactService.removeContact(contactId);			// call removeContac()
	
	        // Assert successful deletion
	        assertFalse(contacts.containsKey(contactId), "Contact is removed from collection");
	        assertTrue(contacts.isEmpty(), "Contacts collection is empty after deletion");
	    }

	    @Test
	    @DisplayName("Should throw IllegalArgumentException when contactId does not exist")
	    /*===================================================================
		 [5] Test deleting non-existing collection contactId
		 *===================================================================  
	   */
	    void shouldThrowExceptionWhenIdDoesNotExist() {
	        String nonExistentId = "10101010";
	
	        // call removeContact() method
	        IllegalArgumentException exception = assertThrows(
	            IllegalArgumentException.class, 
	            () -> contactService.removeContact(nonExistentId),  		// call removeContact() method
	            "Expected deleteContact to throw"
	        );
	        assertEquals("contactId not found", exception.getMessage());
	    }
	    
	    @Test
        @DisplayName("Should successfully update first name")
	    /*===================================================================
		 [6] Test updating firstName in contact collection with given contactID
		 *===================================================================  
	   */
        void testUpdateFirstNameMethodSuccess() {
            contactService.updateFirstName(validId, "Jane");				// call firstName() method
            Contact updated = contacts.get(validId); 
            assertEquals("Jane", updated.getFirstName());
        }
	    
        @Test
        @DisplayName("Should successfully update last name")
        /*===================================================================
		 [7] Test updating lastName in contact collection with given contactID
		 *===================================================================  
		 */
        void testUpdateLastNameMethodSuccess() {
            contactService.updateLastName(validId, "Smith");				// call lastName() method
            Contact updated = contacts.get(validId); 
            assertEquals("Smith", updated.getLastName());
        }
        
        @Test
        @DisplayName("Should successfully update phone number")
        /*===================================================================
		 [8] Test updating phone in contact collection with given contactID
		 *===================================================================  
		 */
        void testUpdateNumberMethodSuccess() {
            contactService.updatePhone(validId, "0987654321");  			// call updatePhone() method
            Contact updated = contacts.get(validId); 
            assertEquals("0987654321", updated.getPhone());
        }
        
        @Test
        @DisplayName("Should successfully update address")
        /*===================================================================
		 [9] Test updating address in contact collection with given contactID
		 *===================================================================  
		 */
        void testUpdateAddressMethodSuccess() {
            contactService.updateAddress(validId, "456 Oak Ave");			// call updateAddress() method
            Contact updated = contacts.get(validId); 
            assertEquals("456 Oak Ave", updated.getAddress());
        }
	}
}
