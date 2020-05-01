#pragma once
class Score
{
public:
	void init();
	int getAmount() const;
	void updateAmount(int);
private:
	int amount_;
};