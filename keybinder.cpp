#include <iostream>
#include "keybinder.h"

Key::Key(const std::string &key_name) :
    key_name_(key_name)
{
}

std::string Key::get_value()
{
    return key_name_;
}

ModifierKey::ModifierKey(const std::string &modifier_name) :
    modifier_name_(modifier_name)
{
}

std::string ModifierKey::get_value()
{
    return modifier_name_;
}

KeyRule::KeyRule() :
    keys_()
{
}

void KeyRule::add_key(const std::string &key_name)
{
    std::tr1::shared_ptr<AbstractKey> key(new Key(key_name));
    keys_.push_back(key);
}

void KeyRule::add_modifier(const std::string &modifier)
{
    std::tr1::shared_ptr<AbstractKey> key(new ModifierKey(modifier));
    keys_.push_back(key);
}

void KeyRule::print()
{
    for (std::vector<std::tr1::shared_ptr<AbstractKey> >::const_iterator iter = keys_.begin(); iter != keys_.end(); ++iter)
    {
        std::cout << iter->get()->get_value() << " ";
    }
    std::cout << std::endl;
}

KeyRule *KeyBinder::add_rule()
{
    std::tr1::shared_ptr<KeyRule> rule_ptr(new KeyRule);
    rules_.push_back(rule_ptr);
    return rule_ptr.get();
}

