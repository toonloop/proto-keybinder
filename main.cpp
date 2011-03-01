/**
 * Prototype for key stuff
 */
#include <clutter/clutter.h>

static const gint WIN_W = 640;
static const gint WIN_H = 480;

#define UNUSED(x) ((void) (x))

typedef struct app_
{
    ClutterActor *rectangle;
} App;

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

    self->rectangle = clutter_rectangle_new_with_color(&red);
    clutter_actor_set_size(self->rectangle, 200, 200);
    clutter_container_add_actor(CLUTTER_CONTAINER(stage), self->rectangle);
    
    g_signal_connect(stage, "key-press-event", G_CALLBACK(key_event_cb), self);
    clutter_actor_show(stage);
    clutter_main();

    g_free(self);

    return 0;
}

