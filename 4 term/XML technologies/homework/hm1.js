function sortString(str) {
    return str.split('').sort().join('');
}

function anagram(words) {
    const groups = {};
    for (const word of words) {
        const sortedWord = sortString(word);
        if (groups[sortedWord]) {
            groups[sortedWord].push(word);
        } else {
            groups[sortedWord] = [word];
        }
    }

    const result = [];
    for (const sortedWord in groups) {
        if (groups[sortedWord].length >= 2) {
            result.push(groups[sortedWord].sort());
        }
    }

    return result;
}

// Пример использования
const words = ['cat', 'act', 'arc'];
const groupedAnagrams = anagram(words);
console.log(groupedAnagrams);
