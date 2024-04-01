// Максимальная длина вывода результата
const MAX_RESULT_LENGTH = 10;

// Получаем ссылку на элемент, отображающий результат вычислений и цвет схемы
const resultElement = document.getElementById('result');
const themeButton = document.getElementById('theme_toggle');

// Переменная для хранения текущего значения в калькуляторе
let currentValue = '0';

// Обновление отображения результата с ограничением по длине
function updateDisplay() {
    let displayValue = currentValue.toString(); // Преобразование в строку
    if (displayValue.includes('e+')) {
        const parts = displayValue.split('e+');
        if (parts[0].length > MAX_RESULT_LENGTH) {
            displayValue = parts[0].slice(0, MAX_RESULT_LENGTH) + '...' + 'e+' + parts[1];
        }
    } else {
        if (displayValue.length > MAX_RESULT_LENGTH) {
            displayValue = displayValue.slice(0, MAX_RESULT_LENGTH) + '...';
        }
    }
    resultElement.textContent = displayValue;
}

// Обработчик события нажатия клавиши
document.addEventListener('keydown', (event) => {
    const keyValue = event.key;
    if (!isNaN(parseFloat(keyValue)) || keyValue === '.') {
        handleDigitClick(keyValue);
    } else if (keyValue === '+' || keyValue === '-' || keyValue === '*' || keyValue === '/') {
        handleOperationClick(keyValue);
    } else if (keyValue === 'Enter') {
        handleOperationClick('=');
    } else if (keyValue === 'Escape') {
        handleOperationClick('C');
    } else if (keyValue === 'Backspace') {
        handleOperationClick('Back');
    }
});

// Добавляем обработчики событий для всех кнопок
const buttons = document.querySelectorAll('.my-btn');
buttons.forEach(button => {
    button.addEventListener('click', () => {
        const buttonValue = button.textContent;
        if (!isNaN(parseFloat(buttonValue)) || buttonValue === '.') {
            handleDigitClick(buttonValue);
        } else {
            handleOperationClick(buttonValue);
        }
    });
});

// Обработчик нажатия на кнопки цифр
function handleDigitClick(digit) {
    if (currentValue === '0') {
        currentValue = digit;
    } else {
        currentValue += digit;
    }
    updateDisplay();
}

// Обработчик нажатия на кнопки операций
function handleOperationClick(operation) {
    switch (operation) {
        case 'C':
            currentValue = '0';
            break;
        case '+/-':
            currentValue = (parseFloat(currentValue) * -1).toString();
            break;
        case '%':
            currentValue = (parseFloat(currentValue) / 100).toString();
            break;
        case 'Back':
            currentValue = currentValue.slice(0, -1);
            if (currentValue === '') {
                currentValue = '0';
            }
            break;
        case '=':
            currentValue = eval(currentValue);
            break;
        case '√':
            currentValue = Math.sqrt(parseFloat(currentValue)).toString();
            break;
        case 'x²':
            currentValue = Math.pow(parseFloat(currentValue), 2).toString();
            break;
        case 'x!':
            currentValue = factorial(parseFloat(currentValue)).toString();
            break;
        default:
            currentValue += operation;
            break;
    }
    updateDisplay();
}

// Функция для вычисления факториала числа
function factorial(num) {
    if (num < 0) {
        return NaN;
    }
    if (num === 0 || num === 1) {
        return 1;
    }
    let result = 1;
    for (let i = 2; i <= num; i++) {
        result *= i;
    }
    return result;
}

// Обработчик смены темы
themeButton.addEventListener('click', () => {
    var theme = document.getElementById('theme');
    if (theme.getAttribute('href') === 'light-theme.css') {
        theme.setAttribute('href', 'dark-theme.css');
    } else {
        theme.setAttribute('href', 'light-theme.css');
    }
    // Устанавливаем значение currentValue в '0'
    currentValue = '0';
    // Обновляем отображение
    updateDisplay();
});

// Обработчик отображения всплывающей информации
function toggleDetails(type) {
    var detailsContent = document.getElementById(type + "-details-content");
    detailsContent.classList.toggle("show");
}
