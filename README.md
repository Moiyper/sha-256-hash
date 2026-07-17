# Hello everyone, in this repozitory im demonstration my ability to work ****SHA256 hash*** with **OpenSSL**! 
Im worked in IDE **Visual Studio Community**, and to compile my project open a file:
<img width="190" height="28" alt="image" src="https://github.com/user-attachments/assets/54ab7b32-f749-4f44-9717-63d788e61c8f" />

For working with librarys **OpenSSL** on WINDOWS, im dowloaded package (***openssl-native***) from **Nu-Get**.

## How the program should work:
Input program get from you any text for **sha256** conventer, after **sha256** raw byte text converted in hash text -> output.

## Which aspect was impotant in code:
***Custom DELETER for EVP_MD_CTX***. So, OpenSSL lirarys was written for C, then a memory leak can occur in C++:
```
struct EVP_MD_CTX_DELETER {
	void operator()(EVP_MD_CTX* ctx) const {
		if (ctx) EVP_MD_CTX_free(ctx);
	}
};
```
