import std;
import Set;

int main() {
    try {
        std::cout << "Variant: Sets of unique elements\n\n";

        std::cout << "1: Constructors and output (operator<<)\n";
        Set<int> s_empty;
        std::cout << "Default constructor: " << s_empty << "\n";

        int init_arr[] = { 5, 3, 5, 1, 3 };
        Set<int> s1(init_arr, 5);
        std::cout << "From array {5, 3, 5, 1, 3} (unique): " << s1 << "\n";

        Set<int> s_rand(4, 1, 10);
        std::cout << "Random fill (4 elements from 1 to 10): " << s_rand << "\n\n";

        std::cout << "2: Information methods and access\n";
        std::cout << "Size of s1 (expected 3): " << s1.size() << "\n";
        std::cout << "Is s1 empty? (expected false): " << std::boolalpha << s1.is_empty() << "\n";
        std::cout << "s1[0] (first element): " << s1[0] << "\n";
        std::cout << "Contains 3? (expected true): " << s1.contains(3) << "\n";
        std::cout << "Contains 9? (expected false): " << s1.contains(9) << "\n";
        try {
            std::cout << "Trying to get s1[10]: ";
            std::cout << s1[10] << "\n";
        }
        catch (const std::out_of_range& e) {
            std::cout << "[Expected exception]: " << e.what() << "\n";
        }
        std::cout << "\n";

        std::cout << "3: Adding and removing elements (+, +=, -, -=)\n";
        Set<int> s2 = s1;
        std::cout << "Initial s2: " << s2 << "\n";

        s2 += 10;
        std::cout << "After s2 += 10: " << s2 << "\n";

        s2 -= 1;
        std::cout << "After s2 -= 1: " << s2 << "\n";

        auto s3 = s2 + 20;
        std::cout << "New s3 = s2 + 20: " << s3 << "\n";

        auto s4 = s2 - 3;
        std::cout << "New s4 = s2 - 3: " << s4 << "\n\n";

        std::cout << "4: Set operations (+, -, *)\n";
        int a_arr[] = { 1, 2, 3, 4 };
        int b_arr[] = { 3, 4, 5, 6 };
        Set<int> set_a(a_arr, 4);
        Set<int> set_b(b_arr, 4);

        std::cout << "Set A: " << set_a << "\n";
        std::cout << "Set B: " << set_b << "\n";
        std::cout << "A + B (union) (expected {1, 2, 3, 4, 5, 6}): " << (set_a + set_b) << "\n";
        std::cout << "A - B (difference) (expected {1, 2}): " << (set_a - set_b) << "\n";
        std::cout << "A * B (intersection) (expected {3, 4}): " << (set_a * set_b) << "\n\n";

        std::cout << "5: Comparison (==, !=)\n";
        Set<int> set_a_copy(a_arr, 4);
        std::cout << "A == A copy? " << (set_a == set_a_copy) << "\n";
        std::cout << "A != B? " << (set_a != set_b) << "\n\n";

        std::cout << "6: Working with other types (float, string, pair)\n";
        float f_arr[] = { 1.1f, 2.2f, 1.1f };
        Set<float> set_f(f_arr, 3);
        std::cout << "float: " << set_f << "\n";

        std::string str_arr[] = { "apple", "banana", "apple" };
        Set<std::string> set_str(str_arr, 3);
        std::cout << "string: " << set_str << "\n";

        std::pair<int, double> pair_arr[] = { {1, 1.5}, {2, 2.5}, {1, 1.5} };
        Set<std::pair<int, double>> set_pair(pair_arr, 3);
        std::cout << "pair: " << set_pair << "\n\n";

        std::cout << "7: Task solution: subset check\n";
        int first_arr[] = { 1, 3 };
        int second_arr[] = { 3, 1, 2, 4 };
        Set<int> first(first_arr, 2);
        Set<int> second(second_arr, 4);
        std::cout << "First: " << first << "\n";
        std::cout << "Second: " << second << "\n";
        std::cout << "Are all elements of the first in the second? (expected true): " << is_subset(first, second) << "\n";

        int bad_arr[] = { 1, 7 };
        Set<int> bad(bad_arr, 2);
        std::cout << "Is {1, 7} a subset of the second? (expected false): " << is_subset(bad, second) << "\n\n";

        std::cout << "8: Random object and method demonstration\n";
        Set<int> set_rand(5, 1, 20);
        std::cout << "   Random set_rand: " << set_rand << "\n";
        std::cout << "   Size of set_rand: " << set_rand.size() << "\n";

        Set<int> set_rand_copy(set_rand);
        Set<int> set_rand_assigned;
        set_rand_assigned = set_rand;

        std::cout << "   set_rand == copy: " << (set_rand == set_rand_copy) << "\n";

        set_rand_assigned -= set_rand_assigned[0];
        std::cout << "   Removed first element from copy: " << set_rand_assigned << "\n";
        std::cout << "   set_rand != modified: " << (set_rand != set_rand_assigned) << "\n\n";

        std::cout << "Checking exception throw on invalid index: \n";
        Set<int> err_set;
        err_set[0];
    }
    catch (const std::out_of_range& e) {
        std::cout << "\nSuccessfully caught expected exception: " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        std::cout << "\nUnexpected error: " << e.what() << "\n";
    }
    return 0;
}
