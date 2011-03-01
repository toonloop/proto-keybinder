/**
 * Prototype for key stuff
 */
#include <clutter/clutter.h>
#include <string>
#include <vector>
#include <iostream>
#include <tr1/memory>

static const gint WIN_W = 640;
static const gint WIN_H = 480;

#define UNUSED(x) ((void) (x))

typedef struct app_
{
    ClutterActor *rectangle;
} App;

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

Key::Key(const std::string &key_name) :
    key_name_(key_name)
{
}

std::string Key::get_value()
{
    return key_name_;
}

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

ModifierKey::ModifierKey(const std::string &modifier_name) :
    modifier_name_(modifier_name)
{
}

std::string ModifierKey::get_value()
{
    return modifier_name_;
}

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

KeyRule *KeyBinder::add_rule()
{
    std::tr1::shared_ptr<KeyRule> rule_ptr(new KeyRule);
    rules_.push_back(rule_ptr);
    return rule_ptr.get();
}

void create_stuff()
{
    KeyBinder binder;
    KeyRule *rule;
    rule = binder.add_rule();
    rule->add_key("a");
    rule->add_modifier("control");
    rule->print();
}

static void key_event_cb(ClutterActor *actor, ClutterKeyEvent *event, gpointer data)
{
    UNUSED(actor);
    App *self = static_cast<App *>(data);
    (void) self;
    switch (event->keyval)
    {
        case CLUTTER_Escape:
            clutter_main_quit();
            break;
        case CLUTTER_space:
            break;
        default:
            break;
    }
}

int main(int argc, char *argv[])
{
    clutter_init(&argc, &argv);

    ClutterActor *stage = NULL;
    ClutterColor black = { 0x00, 0x00, 0x00, 0xff };
    ClutterColor red = { 0xff, 0x00, 0x00, 0xff };
    stage = clutter_stage_get_default();
    clutter_stage_set_title(CLUTTER_STAGE(stage), "Key binder proto");
    clutter_stage_set_color(CLUTTER_STAGE(stage), &black);
    clutter_actor_set_size(stage, WIN_W, WIN_H);


    App *self = g_new0(App, 1);
    create_stuff();

    self->rectangle = clutter_rectangle_new_with_color(&red);
    clutter_actor_set_size(self->rectangle, 200, 200);
    clutter_container_add_actor(CLUTTER_CONTAINER(stage), self->rectangle);
    
    g_signal_connect(stage, "key-press-event", G_CALLBACK(key_event_cb), self);
    clutter_actor_show(stage);
    clutter_main();

    g_free(self);

    return 0;
}

