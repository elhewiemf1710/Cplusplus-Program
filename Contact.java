package com.contactservice.model;

public class Contact {

		    private final String contactId; // contact ID is not be updatable.
		    private String firstName;
		    private String lastName;
		    private String phone;
		    private String address;

		    // Constructor of class Conact
		    public Contact(String contactId, String firstName, String lastName, String phone, String address) {
		    	
		        // contact ID String cannot be longer than 10 characters and shall not be null
		        if (contactId == null || contactId.length() > 10) {
		            throw new IllegalArgumentException("Invalid contactId");
		        }
		        this.contactId = contactId;

		     // setters methods  enforce requirements of length of characters and state of objects		        
		        setFirstName(firstName);
		        setLastName(lastName);
		        setPhone(phone);
		        setAddress(address);
		    }
		    
		    /*=============== GETTER METHODS =================================
		     * Getters: one method for every private field
		     * Each getter method retrieves a String variable: contactID, firstName, lastName, phone, address
		     *================================================================
		     */
		    
		    public String getContactId() { return contactId;}
		    public String getFirstName() { return firstName; }
		    public String getLastName() { return lastName; }
		    public String getPhone() { return phone; }
		    public String getAddress() { return address; }
		        
		    /*=============== SETTER METHODS ==================================
		     * Setters with similar conditional checks: one method for each updatable field
		     * No setter provided to contactID that is not updatable
		     * contactId may be added by a constructor but shall not be updated by a setter method 
		     * ================================================================
		     */

		    public void setFirstName(String firstName) {
		    	 // firstName String cannot be longer than 10 characters and shall not be null
		        if (firstName == null || firstName.length() > 10) {
		            throw new IllegalArgumentException("firstName name is either null or greater than 10 characters.");
		        }
		        this.firstName = firstName;
		    }
		    
		    public void setLastName(String lastName) {
		    	 // lastName String cannot be longer than 10 characters and shall not be null
		        if (lastName == null || lastName.length() > 10) {
		            throw new IllegalArgumentException("lastName is either null or greater than 10 characters.");
		        }
		        this.lastName = lastName;
		    }
		    
		    public void setPhone(String phone) {
		    	// phone String must be exactly 10 characters and shall not be null
		    	if (phone == null || phone.length() != 10) {			
		            throw new IllegalArgumentException("Phone number is either null or does not have 10 characters");
		    	}
		        this.phone = phone;
		    }

		    public void setAddress(String address) {
		    	// address String cannot be longer than 30 characters and shall not be null
		        if (address == null || address.length() > 30) {			
		            throw new IllegalArgumentException("Address is either null or greater than 30 characters");
		        }
		        this.address = address;
		    }
		    
}




