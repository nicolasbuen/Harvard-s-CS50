s = input("Text: ")

ponctuation = ['!', '.', '?']
ignores = ['"', "'", ","]

word_counter = 1
sentence_counter = 0
letter_counter = 0


for i in range(len(s)):
    if s[i] == ' ':
        word_counter = word_counter + 1
        
    elif s[i] in ponctuation:
        sentence_counter = sentence_counter + 1
    
    elif s[i] not in ignores:
        letter_counter = letter_counter + 1

L = ((letter_counter * 100) / word_counter) / ((word_counter * 100) / word_counter) * 100
S = ((sentence_counter * 100) / word_counter) / ((word_counter * 100) / word_counter) * 100

grade = 0.0588 * L - 0.296 * S - 15.8

print(f'{word_counter}   {sentence_counter}   {letter_counter}')

if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print(f"Grade {round(grade)}")