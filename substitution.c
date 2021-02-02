#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

string get_text(string prompt);
string capitalise(string text);
bool is_valid(string key);
bool is_unique(string key);
string do_the_cipher_magic(string ptext, string key);

const int KEY_LENGTH = 26;

int main(int argc, char *argv[])
{
    string ptext;
    string ctext;

    // If no second argument was given warn the user and return early
    if (argc < 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // If the key is invalid warn the user and return early
    else if (!is_valid(argv[1]))
    {
        printf("The key must only contain alphabetic characters and be exactly 26 characters long.\n");
        return 1;
    }
    // If the key is invalid warn the user and return early
    else if (!is_unique(capitalise(argv[1])))
    {
        printf("The key must not contain repeated characters.\n");
        return 1;
    }
    // Otherwise continue
    else
    {
            // Get plaintext from the user
            ptext = get_text("plaintext: ");
            // To get ciphertext, pass plaintext and capitalised key to the cipher function
            ctext = do_the_cipher_magic(ptext, capitalise(argv[1]));
            // Print returned ciphertext
            printf("%s\n", ctext);
            return 0;
    }
}


// Cipher function
string do_the_cipher_magic(string ptext, string key)
{
    // Get plaintext's length
    int p_length = strlen(ptext);

    // Characters array & ciphertext string
    char c[p_length + 1];
    string ctext = "";

    // Shift each of the characters in plain text using KEY
    for (int i = 0; i < p_length; i++)
    {
        // Preserve the case & only substitute alphabetical characters!
        if (isalpha(ptext[i]))
        {
            char temp;
            // Check if lower or upper case
            if (isupper(ptext[i]))
            {
                // Find the index of the letter & substitution
                // 'A' is 65 in ASCII, a substitution is 0 in key
                temp = key[ptext[i] - 65];
            }
            else
            {
                // Find the index of the letter & substitution
                // 'a' is 97 in ASCII, a substitution is 0 in key
                temp = tolower(key[ptext[i] - 97]);
            }

            // Append to ciphertext
            c[i] = temp;
        }
        // Leave non-alphabetic characters as they are & append to ciphertext
        else
        {
            c[i] = ptext[i];
        }
    }
    strcpy(ctext, c);
    return ctext;

}

// Helper for validating the cipher KEY
bool is_valid(string key)
{
    // Check that the key is a 26 character alphabetical key
    // If it's not exactly 26 characters - return
    if (strlen(key) != KEY_LENGTH)
    {
        return false;
    }
    else
    {
        // If any of the characters isn't alphabetical - return
        for (int i = 0; i < KEY_LENGTH; i++)
        {
            if (!isalpha(key[i]))
            {
                printf("failed alpha\n");
                printf("%c\n", key[i]);
                return false;
            }
        }
        // Otherwise it's a valid key
        return true;
    }
}

bool is_unique(string key)
{
    // implememnt
    return true;

}

// Helper for getting user input (string of at least 1 char)
string get_text(string prompt)
{
    string s;
    do
    {
        s = get_string("%s", prompt);
    }
    while (strlen(s) < 1);

    return s;
}

// Helper for capitilising strings
string capitalise(string text)
{
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        text[i] = toupper(text[i]);
    }
    return text;
}

