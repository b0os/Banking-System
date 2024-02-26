## Banking-System
The banking application allows the user, i.e., the  bank employee to create a bank account for a specific client. It allows him to list all the available  bank accounts. For each account, it allows him to display the account details, withdraw money and  deposit money.

There are two types of bank accounts. The first type is the basic BankAccount. It holds the 
following data:

• account ID 

• balance       

The following methods apply to this class: 

• Constructor. There are 2 constructors. The first sets the balance to a given value. The second is 

a no-argument constructor and it sets the balance to 0. 
• Setters and getters. These methods allow accessing the private data fields. 
• withdraw. It withdraws an amount of money from the account if the balance is sufficient. 
• deposit. It deposits an amount of money in the account. 
The second type of accounts extends the basic Bank Account and may have some extra data fields 
and operations. It is called SavingsBankAccount. This account requires the user to keep a 
minimum amount of money in the account, which is called the minimum balance, as long as the 
account is open. It also requires him to make deposits that are not less than 100 a time. So, it has 
the following additional data field: 
• minimumBalance This minimum balance takes a default value of 1000 L.E. 
It has the following methods plus those inherited from the parent class: 
• Constructor. The constructor sets the value of the initial balance and the minimum balance. 
Initial balance should be >= min balance. 
• Setters and getters. These methods allow accessing the private data fields. 
• withdraw. It overrides the method withdraw to allow withdrawing money but not below the 
minimum balance. 
• deposit. It deposits an amount of money in the account but only if the amount is >= 100 LE.  
There is also a Client class which holds the basic information of a client like his name, address 
and phone number. It holds a pointer to his bank account. An account also points to its owner. 
The main class that runs the application is BankingApplication. This class displays the main 
menu and accepts the user's choice. It maintains a list of accounts and clients. It allows the user to 
perform operations on a bank account.

>A sample operation of this application looks like the following: 

'''
Welcome to FCAI Banking Application  
1. Create a New Account  
2. List Clients and Accounts  
3. Withdraw Money  
4. Deposit Money  
Cairo University, Faculty of Artificial 
Intelligence  and Information 
Please Enter Choice =========> 1  
Please Enter Client Name =========> Ahmed Ali Salem  
Please Enter Client Address =======> 5 Batn Elzeer St., Giza  
Please Enter Client Phone =======> 0120130140  
What Type of Account Do You Like? (1) Basic (2) Saving – Type 1 or 2 =========> 1  
Please Enter the Starting Balance =========> 1500  
An account was created with ID FCAI-001 and Starting Balance 1500 L.E.  -------------------------------------------------------------------  
Welcome to FCAI Banking Application  
1. Create a New Account  
2. List Clients and Accounts  
3. Withdraw Money  
4. Deposit Money  
Please Enter Choice =========> 3  
Please Enter Account ID (e.g., FCAI-015) =========> FCAI-001  
Account ID: FCAI-001  
Acocunt Type: Basic  
Balance: 1500  
Please Enter The Amount to Withdraw =========> 1550  
Sorry. This is more than what you can withdraw.  
Please Enter The Amount to Withdraw =========> 40  
Thank you.  
Account ID: FCAI-001  
New Balance: 1460  -------------------------------------------------------------------  
Welcome to FCAI Banking Application  
1. Create a New Account  
2. List Clients and Accounts  
3. Withdraw Money  
4. Deposit Money  
Please Enter Choice =========> 2  -------------------------- Ahmed Ali Salem ---------  
Address: 5 Batn Elzeer St., Giza Phone: 01201301400  
Account ID: FCAI-001 (Basic)  
Balance: 1460  ---------------------------------
'''
