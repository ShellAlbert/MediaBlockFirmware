/**
 * @file zconfig.c
 * @author shell.albert@gmail.com
 * @date July 10,2014
 */
#include <zconfig.h>
#include <ctype.h>
/**
 * @brief trim left space of a string
 */
zint32_t
zconfig_trim_left (zint8_t *src, zint8_t *dest)
{
  zint8_t *pp;
  /**
   * check valid of parameters.
   */
  if (src == NULL || dest == NULL || strlen (src) <= 0)
    {
      printf ("error:zconfig_trim_left():invalid parameters!\n");
      return -1;
    }
  pp = src;
  while (*pp != '\0' && isspace(*pp))
    {
      pp++;
    }
  strcpy (dest, pp);
  return 0;
}

/**
 * @brief trim right space of a string
 */
zint32_t
zconfig_trim_right (zint8_t *src, zint8_t *dest)
{
  zint8_t *pp;
  /**
   * check valid of parameters.
   */
  if (src == NULL || dest == NULL || strlen (src) <= 0)
    {
      printf ("error:zconfig_trim_right():invalid parameters!\n");
      return -1;
    }
  pp = src + strlen (src) - 1;
  while (pp >= src && isspace(*pp))
    {
      pp--;
    }
  *(++pp) = '\0';
  strcpy (dest, src);
  return 0;
}

/**
 * @brief get key value from the default configure file
 */
zint32_t
zconfig_get_key (const zint8_t *keyname, zint8_t *keyvalue)
{
  FILE *fp;
  zint8_t buffer_in[MAXKEYLEN];
  zint8_t buffer_out[MAXKEYLEN];
  zint8_t flag_found = 0;
  /**
   * check valid of parameters.
   */
  if (keyname == NULL || keyvalue == NULL)
    {
      return -1;
    }
  if ((fp = fopen (DEF_ZCONFIG_FILE, "r")) == NULL)
    {
      printf ("error:open config file %s failed:%s\n", DEF_ZCONFIG_FILE,
	      strerror (errno));
      return -1;
    }
  //printf("open file ok\n");
  fseek (fp, 0, SEEK_SET);
  while (!feof (fp) && fgets (buffer_in, MAXKEYLEN, fp) != NULL)
    {
      /**
       * trim left space.
       */
      zconfig_trim_left (buffer_in, buffer_out);
      /**
       * do not handle null line.
       */
      if (strlen (buffer_out) <= 0)
	{
	  /**
	   * printf("zero length after trim left\n");
	   */
	  continue;
	}
      /**
       * skip memo line.
       */
      if (buffer_out[0] == '#')
	{
	  /**
	   * printf("bypass memo line:%s\n",buffer_out);
	   */
	  continue;
	}
      /**
       * get key name.
       */
      if (strncmp (keyname, &buffer_out[0], strlen (keyname)) == 0)
	{
	  /**
	   * next char must be '='.
	   */
	  if (buffer_out[strlen (keyname)] != '=')
	    {
	      break;
	    }
	  /**
	   * trim right space.
	   */
	  zconfig_trim_right (buffer_out, buffer_in);
	  /**
	   * printf("trim right ok\n");
	   */

	  /**
	   * copy value out.
	   */
	  strcpy (keyvalue, &buffer_in[strlen (keyname) + 1]);
	  flag_found = 1;
	  break;
	}
      else
	{
	  continue;
	}
    }  			//while()
  fclose (fp);
  /**
   * return value.
   */
  return flag_found ? 0 : -1;
}
/**
 * the end of file,tagged by zsy
 */
