class Solution {
  public:
    bool IsContinuous(vector<int> numbers) {
        int i, min = 20, max = -20;
        unordered_set<int> card;
        for (i = 0; i < numbers.size(); ++i) {
            if (0 == numbers[i]) continue;
            if (card.find(numbers[i]) != card.end()) return false;
            card.insert(numbers[i]);
            min = min > numbers[i] ? numbers[i] : min;
            max = max < numbers[i] ? numbers[i] : max;
        }
        return (max - min < 5);
    }
};