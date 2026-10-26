package com.contactservice.model;

import java.util.HashMap;
import java.util.Map;

public class ContactService {    
	
	// In-memory data structure HashMap retains temporary data during runtime
    private final Map<String, Contact> contacts = new HashMap<>();
    
    /* ==================ADD CONTACT METHODS ====================================
     * The contact service shall be able to add contacts with a unique ID.
     * Method to add a new Contact type of class Contact 
     * Each contact type contains: contactId, fisrtName, lastName, phone, and address
     * ==========================================================================
     */
    public void addContact(Contact contact) {
    	
    	// Collection contact shall not be empty
        if (contact == null) {
            throw new IllegalArgumentException("contactId invalid");
        }
        // VALIDATION: Ensure contactId is not null or empty
        else if (contact.getContactId() == null || contact.getContactId().trim().isEmpty()) {
            throw new IllegalArgumentException("contactId invalid");
        }
       
        /*
         * Prevent duplicate contactID in memory-stored collection "contacts"
         * The contact object shall have a required unique contact ID
         */
       
        else if (contacts.containsKey(contact.getContactId())) {
           throw new IllegalArgumentException("contactId already exists");
       }
        
        // Datatype contacts holds collections of contact identified by their contact ID String
        contacts.put(contact.getContactId(), contact);
    }
    
    /*================== REMOVE CONTACT METHODS ================================
     * The contact service shall be able to delete contacts per contact ID.
     * ==========================================================================
     */

    public void removeContact(String contactId) {
        if (!contacts.containsKey(contactId)) {
            throw new IllegalArgumentException("contactId not found");
        }
        contacts.remove(contactId);
    }
    
    /*================== UPDATE CONTACT METHODS ================================
     * Updating for fields through setters
     * ==========================================================================
     */
    
    // Update firstName of contact with specific ID by setter method
    public void updateFirstName(String contactID, String firstName) {
        Contact contact = getExistingContact(contactID);
        contact.setFirstName(firstName);
    }
    // Update lastName of contact with specific ID by setter method
    public void updateLastName(String contactID, String lastName) {
        Contact contact = getExistingContact(contactID);
        contact.setLastName(lastName);
    }
    // Update phone of contact with specific ID by setter method
    public void updatePhone(String contactID, String phone) {
        Contact contact = getExistingContact(contactID);
        contact.setPhone(phone);
    }
    // Update address of contact with specific ID by setter method
    public void updateAddress(String contactID, String address) {
        Contact contact = getExistingContact(contactID);
        contact.setAddress(address);
    }
    /*=========================================================================
     * Method to ensure that records with contact ID exists
     * Helper method to retrieve or throw exception if missing
     * =========================================================================
     */
    // Searching and getting the contact collection with specified ID from the HashMap storage datatype
    public Contact getExistingContact(String contactID) {
        if (contactID == null || !contacts.containsKey(contactID)) {
            throw new IllegalArgumentException("contactId not found or invalid.");
        }
        return contacts.get(contactID);
    }
    
}


