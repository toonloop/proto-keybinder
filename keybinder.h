#include <clutter/clutter.h>
#include <string>
#include <vector>
#include <tr1/memory>

#ifndef __KEYBINDER_H__
#define __KEYBINDER_H__

/**
 * Component for a keyboard shortcut.
 */
class AbstractKey
{
    public:
        virtual std::string get_value() = 0;
};

/**
 * Letter component for a keyboard shortcut.
 */
class Key : public AbstractKey
{
    public:
        Key(const std::string &key_name);
        virtual std::string get_value();
    private:
        std::string key_name_;
};

/**
 * Modifier component for a keyboard shortcut.
 */
class ModifierKey : public AbstractKey
{
    public:
        ModifierKey(const std::string &modifier_name);
        virtual std::string get_value();
    private:
        std::string modifier_name_;
};

/**
 * One key binding rule.
 */
class KeyRule
{
    public:
        KeyRule();
        /**
         * Can be any letter, number or some other key.
         */
        void add_key(const std::string &key_name);
        void add_modifier(const std::string &modifier);
        //TODO: void set_action(const std::string &name, const std::string &argument);
        void print();
    private:
        std::vector<std::tr1::shared_ptr<AbstractKey> > keys_;
};

/**
 * Binds key events to actions according to rules.
 */
class KeyBinder
{
    public:
        KeyBinder()
        {
        }
        KeyRule *add_rule();
    private:
        std::vector<std::tr1::shared_ptr<KeyRule> > rules_;
};

#endif

