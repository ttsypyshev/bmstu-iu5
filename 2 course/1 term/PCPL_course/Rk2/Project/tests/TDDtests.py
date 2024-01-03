import unittest
from sources.main import *


# Тестирование класса «Язык программирования»
class TestProgrammingLanguage(unittest.TestCase):

    def test_programming_language_creation(self):
        python = ProgrammingLanguage(1, "Python")
        self.assertEqual(python.language_id, 1)
        self.assertEqual(python.name, "Python")


# Тестирование класса «Синтаксическая конструкция»
class TestSyntaxConstruction(unittest.TestCase):

    def test_syntax_construction_creation(self):
        loop = SyntaxConstruction(1, "Loop", 2, 1)
        self.assertEqual(loop.construction_id, 1)
        self.assertEqual(loop.construction_type, "Loop")
        self.assertEqual(loop.complexity, 2)
        self.assertEqual(loop.language_id, 1)


# Тестирование класса для реализация связи многие ео многим
class TestLanguageSyntaxMap(unittest.TestCase):

    def test_language_syntax_map_creation(self):
        language_map = LanguageSyntaxMap(1, 1)
        self.assertEqual(language_map.language_id, 1)
        self.assertEqual(language_map.construction_id, 1)


class TestMainFunctions(unittest.TestCase):
    # Генерация тестовых данных
    def setUp(self):
        self.languages, self.constructions, _ = get_test_data()

    # Тестирование запроса №1
    def test_get_languages_with_constructions(self):
        result = get_languages_with_constructions(self.languages, self.constructions)
        # Assuming that the result is correct based on the provided data
        self.assertEqual(result, [('C#', ['Function', 'Loop']), ('C++', ['Condition', 'Function']),
                                  ('GoLang', ['Loop', 'Condition', 'Function']), ('Python', ['Loop', 'Condition'])])

    # Тестирование запроса №2
    def test_get_avg_complexity_by_language(self):
        result = get_avg_complexity_by_language(self.languages, self.constructions)
        # Assuming that the result is correct based on the provided data
        self.assertEqual(result, [('Python', 2.5), ('C#', 3.0), ('GoLang', 3.0), ('C++', 3.5)])

    # Тестирование запроса №3
    def test_get_languages_with_related_constructions(self):
        keyword = "Lang"
        result = get_languages_with_related_constructions(self.languages, self.constructions, keyword)
        # Assuming that the result is correct based on the provided data
        self.assertEqual(result, [('GoLang', ['Loop', 'Condition', 'Function'])])


if __name__ == '__main__':
    unittest.main()
