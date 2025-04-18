#include <stdio.h>
#include <stdbool.h>

#define CHILDREN_INITIAL_SIZE 10

typedef enum {
    ROOT,
    OBJECT,
    ARRAY,
    NUMBER,
    STRING
} Element_type;

typedef struct Element {
    Element_type type;
    struct Element* parent;
    struct Element** children;
    int num_children;
    int max_children;
    void* value;
} Element;

int day12_pt1();
int day12_pt2();
int sum_without_red(Element* root);
bool has_red(Element* root);
struct Element* parse_input();
void debug_print(Element* root, int depth);
void add_child(struct Element* parent, struct Element* child);
struct Element* initialize_element();

int day12_pt2()
{
    return sum_without_red(parse_input());
}

int sum_without_red(Element* root)
{
    int sum = 0;

    if (root->type == OBJECT && has_red(root))
    {
        return 0;
    }

    for (int i = 0; i < root->num_children; i++)
    {
        if (root->children[i]->type == NUMBER)
        {
            sum += (int)root->children[i]->value;
        }
        else if(root->children[i]->type != STRING)
        {
            sum += sum_without_red(root->children[i]);
        }
    }

    return sum;
}

bool has_red(Element* root)
{
    for (int i = 0; i < root->num_children; i++)
    {
        if (root->children[i]->type == STRING)
        {
            if (strcmp((char*)root->children[i]->value, "red") == 0)
            {
                return true;
            }
        }
    }

    return false;
}

struct Element* parse_input()
{
    FILE* fp;
    char* line_buffer;
    char* temp_buffer;
    int temp_buffer_offset = 0;
    struct Element* root;
    struct Element* current;
    struct Element* temp = malloc(69);
    bool colon_started = false;
    bool colon_ended = false;
    bool number_started = false;
    root = initialize_element(ROOT);
    current = root;
    fp = fopen("input/day12.txt", "r");
    line_buffer = malloc(1024 * 1024);
    temp_buffer = malloc(1024);

    fgets(line_buffer, 1024 * 1024, fp);

    for (int i = 0; line_buffer[i] != 0; i++)
    { 
        if (number_started && (line_buffer[i] < '0' || line_buffer[i] > '9'))
        {
            number_started = false;
            temp = initialize_element(NUMBER);
            temp_buffer[temp_buffer_offset] = 0;
            temp_buffer_offset++;
            temp->value = malloc(sizeof(int));
            temp->value = strtol(temp_buffer, NULL, 0);
            temp_buffer_offset = 0;
            add_child(current, temp);
        }
        else if (line_buffer[i] == '[')
        {
            temp = initialize_element(ARRAY);
            temp->parent = current;
            add_child(current, temp);
            current = temp;
        }
        else if (line_buffer[i] == '{')
        {
            temp = initialize_element(OBJECT);
            temp->parent = current;
            add_child(current, temp);
            current = temp;
        }
        else if (line_buffer[i] != '"' && colon_started)
        {
            temp_buffer[temp_buffer_offset] = line_buffer[i];
            temp_buffer_offset++;
        }
        else if (line_buffer[i] == '"' && colon_started)
        {
            colon_started = false;
            colon_ended = true;
        }
        else if (line_buffer[i] == '"')
        {
            colon_started = true;
        }
        else if (colon_ended)
        {
            colon_started = false;
            colon_ended = false;

            if (line_buffer[i] != ':')
            {
                temp = initialize_element(STRING);
                temp->parent = current;
                temp_buffer[temp_buffer_offset] = 0;
                temp_buffer_offset++;
                temp->value = malloc(1024);
                strcpy(temp->value, temp_buffer);
                add_child(current, temp);
            }

            temp_buffer_offset = 0;
        }
        else if ((line_buffer[i] >= '0' && line_buffer[i] <= '9') || line_buffer[i] == '-')
        {
            number_started = true;
            temp_buffer[temp_buffer_offset] = line_buffer[i];
            temp_buffer_offset++;
        }

        if (line_buffer[i] == '}' || line_buffer[i] == ']')
        {
            current = current->parent;
        }
    }

    free(temp);
    free(temp_buffer);
    free(line_buffer);
    fclose(fp);

    return root;
}

void debug_print(Element* root, int depth)
{
    for (int i = 0; i < depth; i++)
    {
        printf("    ");
    }
    printf("%d -----------------\n", root->type);
    for (int i = 0; i < root->num_children; i++)
    {
        if (root->children[i] != NULL)
        {
            if (root->children[i]->type == NUMBER || root->children[i]->type == STRING)
            {
                for (int i = 0; i < depth; i++)
                {
                    printf("    ");
                }
            }
            if (root->children[i]->type == NUMBER)
            {
                printf("%d\n", (int*)root->children[i]->value);
            }
            else if (root->children[i]->type == STRING)
            {
                printf("%s\n", (char*)root->children[i]->value);
            }
            else
            {
                debug_print(root->children[i], depth + 1);
            }
        }
    }
}

void add_child(struct Element* parent, struct Element* child)
{
    if (parent->num_children >= parent->max_children)
    {
        parent->children = realloc(parent->children, sizeof(Element*) * (parent->max_children + CHILDREN_INITIAL_SIZE));
    }

    parent->children[parent->num_children] = child;
    parent->num_children++;
}

struct Element* initialize_element(enum Element_type element_type)
{
    struct Element* element = malloc(sizeof(struct Element));
    element->type = element_type;

    switch (element_type)
    {
    case ROOT:
        element->children = (Element**)malloc(sizeof(Element*) * CHILDREN_INITIAL_SIZE);
        element->num_children = 0;
        element->max_children = CHILDREN_INITIAL_SIZE;
        break;
    case OBJECT:
        element->children = (Element**)malloc(sizeof(Element*) * CHILDREN_INITIAL_SIZE);
        element->num_children = 0;
        element->max_children = CHILDREN_INITIAL_SIZE;
        break;
    case ARRAY:
        element->children = (Element**)malloc(sizeof(Element*) * CHILDREN_INITIAL_SIZE);
        element->num_children = 0;
        element->max_children = CHILDREN_INITIAL_SIZE;
        break;
    case NUMBER:
        element->children = NULL;
        element->num_children = 0;
        element->max_children = 0;
        break;
    case STRING:
        break;
    }

    return element;
}

int day12_pt1()
{
    FILE* fp;
    char* line_buffer;
    char* number_buffer;
    int number_buffer_offset = 0;
    int sum = 0;
    fp = fopen("input/day12.txt", "r");
    line_buffer = malloc(1024 * 1024);
    number_buffer = malloc(1024);

    fgets(line_buffer, 1024 * 1024, fp);

    for (int i = 0; line_buffer[i] != 0; i++)
    {
        if ((line_buffer[i] >= '0' && line_buffer[i] <= '9') || line_buffer[i] == '-')
        {
            number_buffer[number_buffer_offset] = line_buffer[i];
            number_buffer_offset++;
        }
        else
        {
            if(number_buffer_offset > 0) {
                number_buffer[number_buffer_offset] = '\0';
                sum += strtol(number_buffer, NULL, 10);
                number_buffer_offset = 0;
            }
        }
    }

    free(line_buffer);
    free(number_buffer);
    fclose(fp);

    return sum;
}