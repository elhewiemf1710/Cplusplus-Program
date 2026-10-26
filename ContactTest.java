package com.contactservice.model;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;


class ContactTest {

	@Test
	@DisplayName("Should successfully check all five members of contact collection with assertionTrue")
	void testContactAffirmative() {
		// Using input data to test setters and constructor on entering data to memory storage  
		Contact contact = new Contact("1234567", "Smith", "Alfred", "9733331444", "2314 main stre");
		
		// testing whether firstName setter accomplished its assigned function
		assertTrue(contact.getFirstName().equals("Smith"));
		
		// testing whether lastName setter accomplished its assigned function
		assertTrue(contact.getLastName().equals("Alfred"));
		
		// testing whether phone setter accomplished its assigned function
		assertTrue(contact.getPhone().equals("9733331444"));
		
		// testing whether constructor accomplished its assigned function of entering valid contactId
		assertTrue(contact.getContactId().equals("1234567"));
		
		// testing whether address setter accomplished its assigned function
		assertTrue(contact.getAddress().equals("2314 main stre"));
		
	}
	
	@Test
	@DisplayName("Should successfully check all five members of contact collection with assertionEquals")
	void testContactNegative() {
		Contact contact = new Contact("1234567", "Smith", "Alfred", "9733331444", "2314 main stre");
		assertEquals("Smith", contact.getFirstName());
		assertEquals("Alfred", contact.getLastName());
		assertEquals("9733331444", contact.getPhone());
		assertEquals("1234567", contact.getContactId());
		assertEquals("2314 main stre", contact.getAddress());
		
	}
	
	@Test
	@DisplayName("Should throw exceptions if any conditional requirement is violated")
	void testContactInvalidPhoneNumber() {
		// Input data in constructor are varied to check every conditional requirement imposed
		// on any member of the contact collection
		assertThrows(IllegalArgumentException.class, ()->{
			new Contact("1234567", "Smith", "Alfred", "97333314440", "2314 main stre");
		
		});	
	}

}
