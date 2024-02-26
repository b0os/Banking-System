# Banking System

This Banking System application allows bank employees to manage client accounts efficiently. It enables creating new bank accounts, listing clients and their accounts, as well as performing withdrawal and deposit operations.

### Technologies Used:
- C++ for the application logic
- SQLite for database management

The application utilizes SQLite to store and manage bank account details, providing a strong and efficient solution for data storage.

---

## Classes and Functionality

### BankAccount
- Holds basic data for a bank account, including account ID and balance.
- Constructors:
  - Sets the balance to a given value.
  - Sets the balance to 0 (default constructor).
- Setters and getters for private data fields.
- `withdraw(amount)`: Withdraws an amount of money from the account if the balance is sufficient.
- `deposit(amount)`: Deposits an amount of money into the account.

### SavingsBankAccount (Inherits from BankAccount)
- Extends the basic BankAccount with additional functionality.
- Requires a minimum balance to be maintained.
- Requires deposits of at least 100 LE.
- Additional data field:
  - minimumBalance (default value of 1000 LE).
- Overrides `withdraw` method to enforce minimum balance.
- Overrides `deposit` method to only accept deposits >= 100 LE.

### Client
- Holds basic information of a client, including name, address, and phone number.


### BankingApplication
- Main class that runs the application.
- Displays a main menu and accepts user input.
- Maintains lists of accounts and clients.
- Allows users to perform operations on bank accounts.

---

## SQLite Database Usage

The banking application utilizes SQLite to store and manage bank account details efficiently. Below is an overview of how SQLite is integrated into the application and its role in storing data:

### Database Structure

The SQLite database consists of a single table named `CLIENTS`, which stores information about bank clients and their accounts. The table schema includes the following fields:

- `ID`: Unique identifier for each client account.
- `NAME`: Client's name.
- `ADDRESS`: Client's address.
- `PHONE`: Client's phone number.
- `TYPE`: Type of bank account (Basic or Saving).
- `BALANCE`: Current balance in the account.

### Integration with the Application

- **Initialization**: Upon starting the application, the SQLite database is opened to allow interaction with client data.

- **Account Creation**: When a bank account is created by a bank employee, the client's information, including their name, address, phone number, chosen account type, and starting balance, is inserted into the `CLIENTS` table.

- **Account Listing**: The application retrieves client information from the `CLIENTS` table to display a list of clients and their associated accounts.

- **Account Operations**: Withdrawal and deposit operations involve updating the account balance in the SQLite database based on user input.

### Error Handling

In case of any database-related errors, appropriate error messages are displayed to the user, ensuring a smooth user experience.

---



## Sample Operation

A sample operation of the application involves creating a new account, withdrawing money, and listing clients and accounts. Below is an example interaction:

```
Welcome to FCAI Banking Application  
1. Create a New Account  
2. List Clients and Accounts  
3. Withdraw Money  
4. Deposit Money  

Please Enter Choice =========> 1  
Please Enter Client Name =========> Ahmed Ali Salem  
Please Enter Client Address =======> 5 Batn Elzeer St., Giza  
Please Enter Client Phone =======> 0120130140  
What Type of Account Do You Like? (1) Basic (2) Saving – Type 1 or 2 =========> 1  
Please Enter the Starting Balance =========> 1500  
An account was created with ID FCAI-001 and Starting Balance 1500 L.E.  

Welcome to FCAI Banking Application  
1. Create a New Account  
2. List Clients and Accounts  
3. Withdraw Money  
4. Deposit Money  

Please Enter Choice =========> 3  
Please Enter Account ID (e.g., FCAI-015) =========> FCAI-001  
Account ID: FCAI-001  
Account Type: Basic  
Balance: 1500  
Please Enter The Amount to Withdraw =========> 1550  
Sorry. This is more than what you can withdraw.  
Please Enter The Amount to Withdraw =========> 40  
Thank you.  
Account ID: FCAI-001  
New Balance: 1460  

Welcome to FCAI Banking Application  
1. Create a New Account  
2. List Clients and Accounts  
3. Withdraw Money  
4. Deposit Money  

Please Enter Choice =========> 2  

-------------------------- Ahmed Ali Salem ---------  
Address: 5 Batn Elzeer St., Giza  
Phone: 01201301400  
Account ID: FCAI-001 (Basic)  
Balance: 1460  
```

This repository contains the source code for the banking application as well as this README file. Feel free to explore the code and use it as a reference 
